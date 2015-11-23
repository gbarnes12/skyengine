#include "stdafx.h"
#include "skyEffectResourceLoader.h"


skyEffectResourceLoader::skyEffectResourceLoader()
{
	m_arrExtensions.push_back("*.effect");
}

skyResult skyEffectResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	return SKY_NOT_IMPLEMENTED;
}

skyResult skyEffectResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyEffectResource* pResource = nullptr;
	SKY_VR(skyEffectResource::Spawn(a_sDesc, &pResource));
    *a_pResource = pResource;
	return SKY_OK;
}