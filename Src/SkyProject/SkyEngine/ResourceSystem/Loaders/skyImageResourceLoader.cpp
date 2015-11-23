#include "stdafx.h"
#include "skyImageResourceLoader.h"


skyImageResourceLoader::skyImageResourceLoader()
{
	m_arrExtensions.push_back("*.jpg");
	m_arrExtensions.push_back("*.png");
	m_arrExtensions.push_back("*.dds");
	m_arrExtensions.push_back("*.bmp");
}

skyResult skyImageResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	skyResult hr;
	skyImageResource* pResource = nullptr;
	SKY_VR(skyImageResource::Spawn(a_sInfo, &pResource));
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyImageResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyImageResource* pResource = nullptr;
	SKY_VR(skyImageResource::Spawn(a_sDesc, &pResource));
	SKY_VR_FAIL(pResource->CreateTexture());
    *a_pResource = pResource;
	return SKY_OK;
FAILED:
	SKY_SAFE_DELETE(pResource);
	return SKY_ERROR;
}