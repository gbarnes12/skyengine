#include "stdafx.h"
#include "skyImageResource.h"
#include "..\skyResource.h"
#include "..\..\ResourceSystem\skyResourceManager.h"
#include "skyImageUtils.h"



skyResult skyImageUtils::Load(skyString a_strName, skyImageResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	SKY_VR(skyResourceManager::Load(a_strName, &pResource));

	// cast back to the shader resource :)
	*a_pResource = static_cast<skyImageResource*>(pResource);
	(*a_pResource)->SetFilename(a_strName);

	return SKY_OK;
}

skyResult skyImageUtils::Request(skyImageResource* a_pResource, eResourceRequestMode a_eRequestMode)
{
	return skyResourceManager::Request(a_pResource, a_eRequestMode);
}

skyResult skyImageUtils::Create(sGfxTextureDesc& a_sDesc, skyImageResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	sImageResourceCreateDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sImageResourceCreateDesc));
	sDesc.m_sTextureDesc = a_sDesc;
	sDesc.m_strType = "Image";
	SKY_VR(skyResourceManager::Create(&sDesc, &pResource));

	*a_pResource = static_cast<skyImageResource*>(pResource);

	return SKY_OK;
}