#include "stdafx.h"
#include "skyMaterialResourceLoader.h"


skyMaterialResourceLoader::skyMaterialResourceLoader()
{
	m_arrExtensions.push_back("*.mat");
}

skyResult skyMaterialResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	skyResult hr;
	skyMaterialResource* pResource = nullptr;
	SKY_VR(skyMaterialResource::Spawn(a_sInfo, &pResource));
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyMaterialResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyMaterialResource* pResource = nullptr;
	SKY_VR(skyMaterialResource::Spawn(&pResource));
    *a_pResource = pResource;
	return SKY_OK;
}