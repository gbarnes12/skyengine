#include "stdafx.h"
#include "..\skyResource.h"
#include "..\..\ResourceSystem\skyResourceManager.h"
#include "skyShaderResource.h"
#include "skyShaderUtils.h"

skyResult skyShaderUtils::Load(skyString a_strName, skyShaderResource** a_pResource, sGfxShaderDesc& a_sDesc)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	SKY_VR(skyResourceManager::Load(a_strName, &pResource));

	// cast back to the shader resource :)
	*a_pResource = static_cast<skyShaderResource*>(pResource);
	(*a_pResource)->SetDesc(a_sDesc);
	return SKY_OK;
}

skyResult skyShaderUtils::Request(skyShaderResource* a_pResource, eResourceRequestMode a_eRequestMode)
{
	return skyResourceManager::Request(a_pResource, a_eRequestMode);
}

skyResult skyShaderUtils::CreateEffect (sGfxShaderDesc& a_sVertexShaderDesc, sGfxShaderDesc& a_sPixelShaderDesc, skyEffectResource** a_pResource)
{
	skyIResource* pResource = nullptr;
	skyResult hr;
	sEffectResourceCreateDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sEffectResourceCreateDesc));
	sDesc.m_sPixelShaderDesc = &a_sPixelShaderDesc;
	sDesc.m_sVertexShaderDesc = &a_sVertexShaderDesc;
	sDesc.m_strType = "Effect";
	SKY_VR(skyResourceManager::Create(&sDesc, &pResource));

	*a_pResource = static_cast<skyEffectResource*>(pResource);
	return SKY_OK;
}