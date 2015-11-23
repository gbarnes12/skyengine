#include "stdafx.h"
#include "skyShaderResourceLoader.h"


skyShaderResourceLoader::skyShaderResourceLoader()
{
	m_arrExtensions.push_back("*.hlsl");
	m_arrExtensions.push_back("*.cso");
}

skyResult skyShaderResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource)
{
	skyResult hr;
	skyShaderResource* pResource = nullptr;
	SKY_VR(skyShaderResource::Spawn(a_sInfo, &pResource));
	*a_pResource = pResource;

	return SKY_OK;
}

skyResult skyShaderResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource)
{
	skyResult hr;
	skyShaderResource* pResource = nullptr;
	SKY_VR(skyShaderResource::Spawn(a_sDesc, &pResource));
    *a_pResource = pResource;
	return SKY_OK;
}