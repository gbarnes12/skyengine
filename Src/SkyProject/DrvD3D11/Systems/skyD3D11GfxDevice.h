#pragma once 

class skyD3D11GfxDevice
	: public skyIGfxDevice 
{
public:
	static skyResult skyD3D11GfxDevice::Spawn ( sGfxDeviceDesc a_sDesc, skyD3D11GfxDevice** a_pDevice);
	skyD3D11GfxDevice::~skyD3D11GfxDevice();

public:
	virtual skyResult skyD3D11GfxDevice::CreateTexture ( skyIGfxTexture** a_pTexture, sGfxTextureDesc& a_sDesc );
	virtual skyResult skyD3D11GfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, sGfxTextureDesc& a_sDesc );
	virtual skyResult skyD3D11GfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, skyIGfxTexture* a_pTexture );
	virtual skyResult skyD3D11GfxDevice::CreateIndexBuffer ( skyIGfxIndexBuffer** a_pBuffer, sGfxIndexDesc& a_sDesc );
	virtual skyResult skyD3D11GfxDevice::CreateVertexBuffer ( skyIGfxVertexBuffer** a_pBuffer, sGfxVertexDesc& a_sDesc ) ;
	virtual skyResult skyD3D11GfxDevice::CreateConstantBuffer ( skyIGfxConstantBuffer** a_pBuffer, sGfxConstantDesc& a_sDesc );
	virtual skyResult skyD3D11GfxDevice::CreatePrimitive ( skyIGfxPrimitive** a_pPrimitive );
	virtual skyResult skyD3D11GfxDevice::CreateShader ( skyIGfxShader** a_pShader, sGfxShaderDesc& a_sDesc );

public:
	virtual skyResult skyD3D11GfxDevice::SetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget* a_pTarget, skyBool a_bUseDepthStencil );
	virtual skyResult skyD3D11GfxDevice::GetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget** a_pTarget );
	virtual skyResult skyD3D11GfxDevice::ClearRenderTarget ( skyUInt a_uiIndex, sGfxColor& a_sColor );
	virtual skyResult skyD3D11GfxDevice::ResetRenderTarget ( skyUInt a_uiIndex ) ;
	virtual skyResult skyD3D11GfxDevice::ResetRenderTargets ( skyVoid );
public:
	virtual skyResult skyD3D11GfxDevice::SetBlendState ( skyIGfxBlendState* a_pState );
	virtual skyResult skyD3D11GfxDevice::SetDepthState ( skyIGfxDepthStencilState* a_pState );
	virtual skyResult skyD3D11GfxDevice::SetRasterizerState ( skyIGfxRasterizerState* a_pState );
	virtual skyResult skyD3D11GfxDevice::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pState );

	virtual skyResult skyD3D11GfxDevice::CreateBlendState ( sGfxBlendDesc a_sDesc, skyIGfxBlendState** a_pState );
	virtual skyResult skyD3D11GfxDevice::CreateDepthState ( sGfxDepthStencilDesc a_sDesc, skyIGfxDepthStencilState** a_pState );
	virtual skyResult skyD3D11GfxDevice::CreateRasterizerState ( sGfxRasterizerDesc a_sDesc, skyIGfxRasterizerState** a_pState );
	virtual skyResult skyD3D11GfxDevice::CreateSamplerState ( sGfxSamplerDesc a_sDesc, skyIGfxSamplerState** a_pState );
public:
	virtual skyResult skyD3D11GfxDevice::SetIndexBuffer ( skyIGfxIndexBuffer* a_pBuffer );
	virtual skyResult skyD3D11GfxDevice::SetVertexBuffer ( skyIGfxVertexBuffer* a_pBuffer, skyUInt a_u32Offset );

public:
	virtual skyVoid skyD3D11GfxDevice::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer );
	virtual skyVoid skyD3D11GfxDevice::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture );

public:
	virtual skyResult skyD3D11GfxDevice::SetDepthBuffer ( skyIGfxDepthBuffer* a_pBuffer);
	virtual skyIGfxDepthBuffer* skyD3D11GfxDevice::GetDepthBuffer ( ) const;
	virtual skyVoid skyD3D11GfxDevice::ClearDepthBuffer ( );
public:
	skyVoid skyD3D11GfxDevice::SetSwapChain ( skyIGfxSwapChain* a_pChain );
public:
	skyVoid skyD3D11GfxDevice::SetViewport ( const sGfxViewport& a_sViewport );
	sGfxViewport skyD3D11GfxDevice::GetViewport ( skyVoid );
public:
	skyResult skyD3D11GfxDevice::GetBackBuffer ( skyIGfxTexture** a_pTexture );
public:
	virtual skyVoid skyD3D11GfxDevice::Draw ( skyIGfxPrimitive* a_pPrimitive );
	virtual skyVoid skyD3D11GfxDevice::Draw ( sGfxDrawDesc& a_sDesc );
public:
	virtual skyVoid skyD3D11GfxDevice::Present ( sGfxPresentDesc& a_sDesc );
public:
	virtual skyVoid skyD3D11GfxDevice::Resize ( skyVoid );
public:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;
	skyD3D11GfxSwapChain* m_pSwapChain;
	skyD3D11ResourceManager* m_pResourceManager;
	skyD3D11GfxStateManager* m_pStateManager;
	skyD3D11DepthBuffer* m_pDepthBuffer;
	skyIGfxRenderTarget* m_pRenderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];

	skyD3D11GfxDevice::skyD3D11GfxDevice(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pContext, 
		skyD3D11ResourceManager* a_pResourceManager, skyD3D11GfxStateManager* a_pStateManager);

};