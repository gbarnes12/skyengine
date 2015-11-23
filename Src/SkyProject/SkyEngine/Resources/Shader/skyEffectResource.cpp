#include "stdafx.h"
#include "..\skyResource.h"
#include "skyEffectResource.h"


skyResult skyEffectResource::Spawn (sIResourceCreateDesc* a_sDesc, skyEffectResource** a_pResource)
{
	sEffectResourceCreateDesc* sDesc = static_cast<sEffectResourceCreateDesc*>(a_sDesc);
	skyShaderResource* pVertexShader = nullptr;
	skyShaderResource* pPixelShader = nullptr;
	skyResult hr;

	// load the shader via resource system
	SKY_VR_FAIL(skyShaderUtils::Load(sDesc->m_sPixelShaderDesc->m_sFileName, &pPixelShader, *sDesc->m_sPixelShaderDesc));
	SKY_VR_FAIL(skyShaderUtils::Load(sDesc->m_sVertexShaderDesc->m_sFileName, &pVertexShader, *sDesc->m_sVertexShaderDesc));
	
	// request it immediately!
	SKY_VR_FAIL(skyShaderUtils::Request(pPixelShader, eResourceRequestMode_Immediate));
	SKY_VR_FAIL(skyShaderUtils::Request(pVertexShader, eResourceRequestMode_Immediate));

	skyEffectResource* pResource = SKY_NEW skyEffectResource(pVertexShader, pPixelShader);
	*a_pResource = pResource;

	return SKY_OK;
FAILED:
	SKY_RELEASE(pVertexShader);
	SKY_RELEASE(pPixelShader);

	return SKY_ERROR;
}

skyEffectResource::~skyEffectResource()
{
}
 
skyResult skyEffectResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	return SKY_NOT_IMPLEMENTED;
}

skyResult skyEffectResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_NOT_IMPLEMENTED;
}

skyResult skyEffectResource::OnCacheOut ()
{
	SKY_RELEASE(m_pVertexShader);
	SKY_RELEASE(m_pPixelShader);
	return SKY_OK;
}

skyVoid skyEffectResource::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture )
{
	skyGfxManager::SetTexture(a_eType, a_uiSlot, a_pTexture);
}

skyVoid skyEffectResource::SetSampler ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxSamplerState* a_pSampler )
{
	skyGfxManager::SetSamplerState(a_eType, a_uiSlot, (skyIGfxSamplerState*)a_pSampler);
}

skyVoid skyEffectResource::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer )
{
	skyGfxManager::SetConstantbuffer(a_eType, a_uiSlot, a_pBuffer);
}

skyVoid skyEffectResource::Execute()
{
	if(m_pVertexShader && m_pPixelShader)
	{
		this->m_pVertexShader->Execute();
		this->m_pPixelShader->Execute();
	}
}