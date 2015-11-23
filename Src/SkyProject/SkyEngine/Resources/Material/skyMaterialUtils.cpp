#include "stdafx.h"
#include "skyMaterialResource.h"
#include "..\skyResource.h"
#include "..\..\ResourceSystem\skyResourceManager.h"
#include "skyMaterialUtils.h"



skyResult skyMaterialUtils::Load(skyString a_strName, skyMaterialResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	SKY_VR(skyResourceManager::Load(a_strName, &pResource));

	// cast back to the shader resource :)
	*a_pResource = static_cast<skyMaterialResource*>(pResource);
	(*a_pResource)->SetName(a_strName);


	return SKY_OK;
}

skyResult skyMaterialUtils::Request(skyMaterialResource* a_pResource, eResourceRequestMode a_eRequestMode)
{
	return skyResourceManager::Request(a_pResource, a_eRequestMode);
}

skyResult skyMaterialUtils::Create(skyMaterialResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	sIResourceCreateDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sIResourceCreateDesc));
	sDesc.m_strType = "Material";

	skyResult hr;
	SKY_VR(skyResourceManager::Create(&sDesc, &pResource));

	*a_pResource = static_cast<skyMaterialResource*>(pResource);

	return SKY_OK;
}