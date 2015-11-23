#include "stdafx.h"
#include "skyResourceSystem.h"
#include "skyResourceCache.h"

skyResult skyResourceCache::Initialize( skyUInt a_uiSize, skyResourceSystem* a_pInstance)
{
	this->m_u32CacheSize = a_uiSize * 1024 * 1024;
	this->m_u32CurrentlyAllocated = 0;
	this->m_pInstance = a_pInstance;
	
	return SKY_OK;
}


skyResult skyResourceCache::Shutdown( )
{
	this->m_mapCache.clear();
	this->m_u32CurrentlyAllocated = 0;
	return SKY_OK;
}

SKY_TODO("check all the functions for errors and log stuff!");
SKY_TODO("make it possible to switch between ");
skyResult skyResourceCache::In ( sResourceInfo& a_sInfo, sIOMemBlob* a_pBlob, skyUInt a_u32AddSize )
{
	skyUInt u32Size = a_sInfo.m_u32FileSizeRaw + a_u32AddSize;
	if (u32Size > m_u32CacheSize)
    {
		return SKY_TOO_LARGE;
    }

	while (u32Size > (m_u32CacheSize - m_u32CurrentlyAllocated))
    {
        // The cache is empty, and there's still not enough room.
		if (m_pInstance->m_arrRecentlyUsedResources.empty())
			return skyResult::SKY_OUT_OF_MEMORY;

		m_pInstance->CacheOutOneResource();
    }

	skyAnsiStr pMemory = SKY_NEW skyAnsiChar[u32Size];
    if (!pMemory)
	{
		SKY_PRINT_CONSOLE("error", "resource cache couldn't allocate anymore memory!", 0x0f);
		return SKY_OUT_OF_MEMORY;
	}
	
	this->m_u32CurrentlyAllocated += u32Size;

	a_pBlob->m_uiBufferPtr = reinterpret_cast<uintptr_t>(pMemory);
	a_pBlob->m_uiBufferSize = u32Size;

	// insert the resource to the cache map so we can keep track of 
	// cached in resources!
	m_mapCache.insert(std::pair<skyULong, sResourceInfo>(a_sInfo.m_ulHash, a_sInfo));

	return SKY_OK;
}

skyVoid skyResourceCache::Out ( sResourceInfo& a_sInfo )
{
	this->m_u32CurrentlyAllocated -= a_sInfo.m_u32FileSizeRaw;
	m_mapCache.erase(a_sInfo.m_ulHash);
}