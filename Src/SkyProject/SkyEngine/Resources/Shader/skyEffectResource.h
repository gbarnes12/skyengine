#pragma once

class skyEffectResource : public skyResource 
{
public:
	//SKY_PROPERTY_GET(skyIGfxShader*, m_pInstance, Shader);

public:
	static skyResult skyEffectResource::Spawn (sIResourceCreateDesc* a_sDesc, skyEffectResource** a_pResource);

public:
	virtual skyEffectResource::~skyEffectResource();

public:
	virtual skyResult skyEffectResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyEffectResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyEffectResource::OnCacheOut ();

public:
	skyVoid skyEffectResource::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer );
	skyVoid skyEffectResource::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture );
	skyVoid skyEffectResource::SetSampler ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxSamplerState* a_pSampler );

public:
	skyVoid skyEffectResource::Execute();

private:
	skyShaderResource* m_pVertexShader;
	skyShaderResource* m_pPixelShader;
	
	skyEffectResource::skyEffectResource(skyShaderResource* a_pVertexShader, skyShaderResource* a_pPixelShader)
		: m_pVertexShader(a_pVertexShader)
		, m_pPixelShader(a_pPixelShader)
	{
	}
};