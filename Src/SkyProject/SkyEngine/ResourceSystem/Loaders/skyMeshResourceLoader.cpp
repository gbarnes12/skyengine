#include "stdafx.h"
#include "skyMeshResourceLoader.h"


skyMeshResourceLoader::skyMeshResourceLoader()
{
	m_arrExtensions.push_back("*.sm");
}

skyResult skyMeshResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	skyResult hr;
	skyMeshResource* pResource = nullptr;
	SKY_VR(skyMeshResource::Spawn(a_sInfo, &pResource));
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyMeshResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyMeshResource* pResource = nullptr;
	SKY_VR(skyMeshResource::Spawn(a_sDesc, &pResource));
    *a_pResource = pResource;
	return SKY_OK;
}