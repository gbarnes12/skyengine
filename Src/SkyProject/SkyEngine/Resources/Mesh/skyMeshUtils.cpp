#include "stdafx.h"
#include "skyMeshResource.h"
#include "..\skyResource.h"
#include "..\..\ResourceSystem\skyResourceManager.h"
#include "skyMeshUtils.h"



skyResult skyMeshUtils::Load(skyString a_strName, skyMeshResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	SKY_VR(skyResourceManager::Load(a_strName, &pResource));

	// cast back to the shader resource :)
	*a_pResource = static_cast<skyMeshResource*>(pResource);


	return SKY_OK;
}

skyResult skyMeshUtils::Request(skyMeshResource* a_pResource, eResourceRequestMode a_eRequestMode)
{
	return skyResourceManager::Request(a_pResource, a_eRequestMode);
}

/*
skyResult skyMeshUtils::Create(sGfxTextureDesc& a_sDesc, skyMeshResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	sImageResourceCreateDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sImageResourceCreateDesc));
	SKY_VR(skyResourceManager::Create(&sDesc, &pResource));

	*a_pResource = static_cast<skyMeshResource*>(pResource);
	return SKY_OK;
}*/