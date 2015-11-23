#include "stdafx.h"
#include "..\skyResource.h"
#include "..\..\ResourceSystem\skyResourceManager.h"
#include "skyGameObjectPrefabUtils.h"



skyResult skyGameObjectPrefabUtils::Load(skyString a_strName, skyGameObjectPrefabResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	SKY_VR(skyResourceManager::Load(a_strName, &pResource));

	// cast back to the shader resource :)
	*a_pResource = static_cast<skyGameObjectPrefabResource*>(pResource);

	return SKY_OK;
}

skyResult skyGameObjectPrefabUtils::Request(skyGameObjectPrefabResource* a_pResource, eResourceRequestMode a_eRequestMode)
{
	return skyResourceManager::Request(a_pResource, a_eRequestMode);
}

skyResult skyGameObjectPrefabUtils::Create(skyGameObjectPrefabResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	sIResourceCreateDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sIResourceCreateDesc));
	sDesc.m_strType = "Prefab";

	skyResult hr;
	SKY_VR(skyResourceManager::Create(&sDesc, &pResource));

	*a_pResource = static_cast<skyGameObjectPrefabResource*>(pResource);

	return SKY_OK;
}