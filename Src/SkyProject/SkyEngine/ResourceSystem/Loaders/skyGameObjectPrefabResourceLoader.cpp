#include "stdafx.h"
#include "skyGameObjectPrefabResourceLoader.h"


skyGameObjectPrefabResourceLoader::skyGameObjectPrefabResourceLoader()
{
	m_arrExtensions.push_back("*.goprefab");
}

skyResult skyGameObjectPrefabResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	skyResult hr;
	skyGameObjectPrefabResource* pResource = nullptr;
	SKY_VR(skyGameObjectPrefabResource::Spawn(a_sInfo, &pResource));
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyGameObjectPrefabResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyGameObjectPrefabResource* pResource = nullptr;
	SKY_VR(skyGameObjectPrefabResource::Spawn(a_sDesc, &pResource));
    *a_pResource = pResource;
	return SKY_OK;
}