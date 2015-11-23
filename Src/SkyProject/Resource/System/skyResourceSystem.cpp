#include "stdafx.h"
#include "inc_resource_interfaces.h"
#include "skyResourceSystem.h"

skyResult skyResourceSystem::Initialize(skyUInt a_u32Size, eResourceMode a_eMode)
{
	skyResult hr;
	m_FileSystem.Mount(&this->m_DiskFileDevice);
	m_FileSystem.Mount(&this->m_ZipFileDevice);

	SKY_VR(m_Database.Initialize(this));
	SKY_VR(m_Cache.Initialize(a_u32Size, this));

	this->m_eMode = a_eMode;

	return SKY_OK;
}

skyResult skyResourceSystem::Shutdown()
{
	skyResult hr;

	while (!m_arrRecentlyUsedResources.empty())
		CacheOutOneResource();

	// Release the resources
	for(skyResourceMap::iterator it = m_mapResources.begin(); it != m_mapResources.end(); it++)
	{
		(*it).second->Release();
		(*it).second = NULL;
	}

	m_mapResources.clear();

	// Release the created resources
	for(skyCreatedResources::iterator it = m_arrCreatedResources.begin(); it != m_arrCreatedResources.end(); it++)
	{
		(*it)->OnCacheOut();
		(*it)->Release();
		(*it) = NULL;
	}

	m_arrCreatedResources.clear();

	SKY_VR(m_Cache.Shutdown());
	SKY_VR(m_Database.Shutdown());

	this->m_arrLoaders.clear();
	return SKY_OK;
}

skyVoid skyResourceSystem::RegisterLoader(skyIResourceLoader* a_pLoader)
{
	if(a_pLoader)
	{
		skyResourceLoaderArray::iterator it = std::find(m_arrLoaders.begin(), m_arrLoaders.end(), a_pLoader);
	
		if(it != m_arrLoaders.end())
			return;

		this->m_arrLoaders.push_back(a_pLoader);
	}
}

skyResult skyResourceSystem::Load ( skyString a_strFile, skyIResource** a_pResource )
{
	skyResult hr;
	sResourceInfo sInfo;
	skyULong ulHash = skyHashedString(a_strFile.c_str()).GetHashValue();

	// search for resource in map!
	if(m_mapResources.find(ulHash) != m_mapResources.end())
	{
		// found just return it!
		*a_pResource = m_mapResources[ulHash];
		Update(*a_pResource);
		return SKY_OK;
	}

	SKY_ZERO_MEM(&sInfo, sizeof(sResourceInfo));
	SKY_VR(m_Database.GetResourceInfo(ulHash, &sInfo));

	skyIResourceLoader* pLoader = FindResourceLoader(&sInfo);

	if(!pLoader) {
		SKY_PRINT_CONSOLE("error", "Couldn't find the necessary resource loader for resource[" + sInfo.m_strFileName + "]", 0x0f);
		return SKY_INVALID_POINTER;
	}

	SKY_VR(pLoader->OnLoadIn(sInfo, a_pResource));

	// set the state!
	(*a_pResource)->SetResourceState(eResourceState_Loaded);
	(*a_pResource)->AddRef();
	m_mapResources.insert(std::pair<skyULong, skyIResource*>(ulHash, *a_pResource));

	return SKY_OK;
}

skyResult skyResourceSystem::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode )
{
	skyResult hr;

	// if resource provided is null just return an error
	if(!a_pResource)
		return SKY_INVALID_POINTER;

	// we actually don't need to request the resource anymore if its still in the cache!
	eResourceState eState = a_pResource->GetResourceState();
	if(eState == eResourceState_CachedIn)
		return SKY_OK;

	// update the resource since we recently used it!
	Update(a_pResource);

	switch(a_eMode)
	{
	case eResourceRequestMode_Immediate:
		hr = RequestImmediate(a_pResource);
		break;
	case eResourceRequestMode_Deferred:
		hr = RequestDeferred(a_pResource);
		break;
	};

	return hr;
}

skyResult skyResourceSystem::RequestImmediate ( skyIResource* a_pResource )
{
	if(!a_pResource)
		return SKY_INVALID_POINTER;

	skyResult hr;
	sResourceInfo& sInfo = a_pResource->GetInfo();
	skyIResourceLoader* pLoader = FindResourceLoader(&sInfo);

	if(!pLoader)
		return SKY_INVALID_POINTER;

	sIOMemBlob sBlob;
	SKY_ZERO_MEM(&sBlob, sizeof(sIOMemBlob));


	// once we cached in we can start open the file for reading!
	skyInt u32Mode = (pLoader->IsBinary()) ? (eFileMode_Read | eFileMode_Binary) : (m_eMode == eResourceMode_Compiled) ? (eFileMode_Read | eFileMode_Binary) : (eFileMode_Read);
	skyIFile* pFile = m_FileSystem.Open("disk",  ".." + sInfo.m_strFilePath + "\\" + sInfo.m_strFileName + "." + sInfo.m_strFileExtension, static_cast<skyFileMode>(u32Mode));

	if(!pFile)
	{
		SKY_PRINT_CONSOLE("error", "Couldn't load file from disk for resource[" + sInfo.m_strFileName + "]", 0x0f);
		return SKY_ERROR;
	}

	// we cache in the resource which means we allocate the memory
	// needed! and we check if space is still there!
	skyUInt u32AddSize = (pLoader->EscapeNull()) ? 1 : 0;
	skyUInt u32Size = sInfo.m_u32FileSizeRaw + u32AddSize;
	SKY_VR_FAIL(m_Cache.In(sInfo, &sBlob, u32AddSize));

	// get buffer and fill it!
	skyVoidPtr pBuffer = (skyVoidPtr)skyGetDataFromBlob<skyAnsiStr>(sBlob);

	if(pLoader->EscapeNull())
		memset((skyVoidPtr)pBuffer, 0, u32Size);

	if(!pBuffer) 
	{
		SKY_PRINT_CONSOLE("error", "Buffer has an invalid pointer (probably ran out of memory) for resource[" + sInfo.m_strFileName + "]", 0x0f);
		m_FileSystem.Close(pFile);
		pFile = NULL;
		return SKY_INVALID_POINTER;
	}

	// read the file into the buffer!
	if(pFile->VRead(pBuffer, u32Size) == -1)
	{
		SKY_SAFE_DELETE_ARRAY(pBuffer);
		m_FileSystem.Close(pFile);
		pFile = NULL;

		SKY_PRINT_CONSOLE("skyResourceSystem", "Couldn't load resource[" + sInfo.m_strFileName + "]", 0x0A);
		return SKY_ERROR; // cache ran out of memory!
	}

	m_FileSystem.Close(pFile);
	pFile = NULL;

	if(m_eMode == eResourceMode_Compiled) {
		SKY_VR_FAIL(pLoader->OnRequestCompiledData(a_pResource, sBlob));
	}
	else {
		SKY_VR_FAIL(pLoader->OnRequestRawData(a_pResource, sBlob));
	}

	SKY_SAFE_DELETE_ARRAY(pBuffer);
	a_pResource->SetResourceState(eResourceState_CachedIn);

	return SKY_OK;
FAILED:
	SKY_SAFE_DELETE_ARRAY(pBuffer);
	m_FileSystem.Close(pFile);
	pFile = NULL;
	return hr;
}

skyResult skyResourceSystem::RequestDeferred ( skyIResource* a_pResource )
{
	SKY_TODO("implement deferred way to request resources! which means full thread safety and thread support");
	assert(false == true);
	return SKY_NOT_IMPLEMENTED;
}

skyResult skyResourceSystem::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  )
{

	skyResult hr;
	skyIResourceLoader* pLoader = nullptr;
	for(skyUInt i = 0; i < m_arrLoaders.size(); i++)
	{
		skyString strType = m_arrLoaders[i]->GetType();
		if(strType == a_sDesc->m_strType)
		{
			pLoader = m_arrLoaders[i];
			break;
		}
	}

	if(!pLoader)  {
		SKY_PRINT_CONSOLE("error", "Couldn't find the necessary resource loader for resource[type: " + a_sDesc->m_strType + "]", 0x0f);
		return SKY_INVALID_POINTER;
	}

	SKY_VR(pLoader->OnCreateResource(a_sDesc, a_pResource));
	
	// set the state!
	(*a_pResource)->SetResourceState(eResourceState_Loaded);
	(*a_pResource)->AddRef();
	m_arrCreatedResources.push_back((*a_pResource));

	return SKY_OK;
}

skyResult skyResourceSystem::CacheOutOneResource (  )
{
	skyRecentlyUsedResourceArray::iterator it = m_arrRecentlyUsedResources.end();
    it--;

    skyULong u32Hash = *it;
    m_arrRecentlyUsedResources.pop_back();     

	skyResult hr;
	skyIResource* pResource = m_mapResources[u32Hash];
	sResourceInfo& sInfo = pResource->GetInfo();
	skyIResourceLoader* pLoader = FindResourceLoader(&sInfo);

	if(!pLoader) {
		SKY_PRINT_CONSOLE("error", "Couldn't find the necessary resource loader for resource[" + sInfo.m_strFileName + "]", 0x0f);
		return SKY_INVALID_POINTER;
	}
	
	SKY_VR(pLoader->OnCacheOut(pResource));
	m_Cache.Out(sInfo);

	return SKY_OK;
}


skyResult skyResourceSystem::CacheOut ( skyIResource* a_pResource )
{
	skyResult hr;
	sResourceInfo& sInfo = a_pResource->GetInfo();
	skyIResourceLoader* pLoader = FindResourceLoader(&sInfo);

	if(!pLoader)
		return SKY_INVALID_POINTER;
	
	SKY_VR(pLoader->OnCacheOut(a_pResource));
	m_Cache.Out(sInfo);

	return SKY_OK;
}

skyIResourceLoader* skyResourceSystem::FindResourceLoader (sResourceInfo* sInfo)
{
	skyIResourceLoader* pLoader = nullptr;
	for(skyUInt i = 0; i < m_arrLoaders.size(); i++)
	{
		std::vector<skyString> arrExtensions = m_arrLoaders[i]->GetExtensions();
		for(skyUInt y = 0; y < arrExtensions.size(); y++)
		{
			skyString strPattern = arrExtensions[y];
			skyString strFilename = (sInfo->m_strFileName + "." + sInfo->m_strFileExtension);
			if(skyWildcardMatch(strPattern.c_str(), strFilename.c_str()))
			{
				pLoader = m_arrLoaders[i];
				break;
			}
		}

		if(pLoader)
			break;
	}

	return pLoader;
}

skyVoid skyResourceSystem::Flush ( )
{
	while (!m_arrRecentlyUsedResources.empty())
    {
        skyULong ulHash = *(m_arrRecentlyUsedResources.begin());
		skyIResource* pResource = m_mapResources[ulHash];
		CacheOut(pResource);
        m_arrRecentlyUsedResources.pop_front();
    }
}

skyVoid skyResourceSystem::Update ( skyIResource* a_pResource )
{
	sResourceInfo& sInfo = a_pResource->GetInfo();
	m_arrRecentlyUsedResources.remove(sInfo.m_ulHash);
	m_arrRecentlyUsedResources.push_front(sInfo.m_ulHash);
}