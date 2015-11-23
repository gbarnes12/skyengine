#pragma once 

class skyD3D11Effect : public skyIGfxEffect, public skyD3D11Resource
{
public:
	skyResult skyD3D11Effect::Spawn (  const skyD3D11GfxDevice* a_pDevice, skyD3D11Effect** a_pEffect );

	virtual skyD3D11Effect::~skyD3D11Effect();
public:
	virtual skyVoid skyD3D11Effect::SetConstantbuffer ( const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer );
	virtual skyVoid skyD3D11Effect::SetTexture ( const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture );
	virtual skyVoid skyD3D11Effect::SetSampler ( const skyUInt a_uiSlot, const skyIGfxSamplerState* a_pSampler );	
public: 
	virtual skyVoid skyD3D11Effect::Apply ( );

private:
	skyD3D11PixelShader* m_pPS; 
	skyD3D11VertexShader* m_pVS;

	skyD3D11Effect::skyD3D11Effect(  const skyD3D11GfxDevice* a_pDevice );
};