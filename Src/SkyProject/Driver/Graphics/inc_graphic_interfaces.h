#pragma once

class skyIGfxResource
{
public:
	virtual skyIGfxResource::~skyIGfxResource() { }
public:
	virtual eGfxResourceType skyIGfxResource::GetType ( skyVoid ) = 0;
};

class skyIGfxIndexBuffer
{
public:
	virtual skyIGfxIndexBuffer::~skyIGfxIndexBuffer() { }
public:
	virtual sGfxIndexDesc skyIGfxIndexBuffer::GetDesc ( skyVoid ) = 0;
public:
	virtual skyVoid* skyIGfxIndexBuffer::GetData ( skyVoid ) const = 0;
public:
	virtual skyResult skyIGfxIndexBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData ) = 0;
	virtual skyVoid skyIGfxIndexBuffer::Unlock ( skyUInt a_uiSubresource ) = 0;
};

class skyIGfxVertexBuffer
{
public:
	virtual skyIGfxVertexBuffer::~skyIGfxVertexBuffer() { }
public:
	virtual sGfxVertexDesc skyIGfxVertexBuffer::GetDesc ( skyVoid ) = 0;
public:
	virtual skyVoid skyIGfxVertexBuffer::SetStride( skyUInt a_u32Stride ) = 0;
	virtual skyUInt skyIGfxVertexBuffer::GetStride( skyVoid ) = 0;
public:
	virtual skyVoid skyIGfxVertexBuffer::SetElementCount( skyUInt a_u32Count ) = 0;
	virtual skyUInt skyIGfxVertexBuffer::GetElementCount( skyVoid ) = 0;
public:
	virtual skyVoid* skyIGfxVertexBuffer::GetData ( skyVoid ) const = 0;
public:
	virtual skyResult skyIGfxVertexBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData ) = 0;
	virtual skyVoid skyIGfxVertexBuffer::Unlock ( skyUInt a_uiSubresource ) = 0;
};

class skyIGfxConstantBuffer
{
public:
	virtual skyIGfxConstantBuffer::~skyIGfxConstantBuffer() { }
public:
	virtual sGfxConstantDesc skyIGfxConstantBuffer::GetDesc ( skyVoid ) = 0;
public:
	virtual skyVoid* skyIGfxConstantBuffer::GetData ( skyVoid ) const = 0;
public:
	virtual skyResult skyIGfxConstantBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData ) = 0;
	virtual skyVoid skyIGfxConstantBuffer::Unlock ( skyUInt a_uiSubresource ) = 0;
};

class skyIGfxDepthBuffer
{
public:
	virtual skyIGfxDepthBuffer::~skyIGfxDepthBuffer() { }
public:
	virtual sGfxDepthStencilDesc skyIGfxDepthBuffer::GetDesc ( skyVoid ) = 0;
	virtual skyIGfxTexture* skyIGfxDepthBuffer::GetDepthTexture ( skyVoid ) = 0;
};


class skyIGfxStructuredBuffer
{
public:
	virtual skyIGfxStructuredBuffer::~skyIGfxStructuredBuffer() { }
public:
	virtual sGfxStructuredDesc skyIGfxStructuredBuffer::GetDesc ( skyVoid ) = 0;
public:
	virtual skyResult skyIGfxStructuredBuffer::SetData ( sGfxConstantDesc& a_pData ) = 0;
	virtual skyVoid* skyIGfxStructuredBuffer::GetData ( skyVoid ) const = 0;
public:
	virtual skyResult skyIGfxStructuredBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, skyVoid* a_pData, skyUInt a_uiSize ) = 0;
	virtual skyResult skyIGfxStructuredBuffer::Unlock ( skyVoid ) = 0;
};

class skyIGfxTexture
{
public:
	virtual skyIGfxTexture::~skyIGfxTexture() { }
public:
	virtual sGfxTextureDesc skyIGfxTexture::GetDesc ( skyVoid ) = 0;
public:
	virtual skyResult skyIGfxTexture::CopyToCurrentRT ( skyVoid ) = 0;
	virtual skyResult skyIGfxTexture::CopyTextureToTexture ( skyIGfxTexture* m_pSource ) = 0;
	virtual skyResult skyIGfxTexture::CopyCurrentRT ( skyVoid ) = 0;
	virtual skyResult skyIGfxTexture::CopyRTToTexture ( skyIGfxRenderTarget* a_pRT ) = 0;
public:
	virtual skyResult skyIGfxTexture::SaveToFile ( skyString a_sFileName ) = 0;
	virtual skyResult skyIGfxTexture::SaveToMemory ( skyVoid* a_pBuffer ) = 0;
public:
	virtual skyVoid* skyIGfxTexture::GetData ( skyVoid )  = 0;
public:
	virtual skyResult skyIGfxTexture::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData ) = 0;
	virtual skyVoid skyIGfxTexture::Unlock ( skyUInt a_uiSubresource ) = 0;
};

class skyIGfxShader
{

public:
	virtual skyIGfxShader::~skyIGfxShader() { }
public:
	virtual eGfxShaderType skyIGfxShader::GetShaderType ( skyVoid ) const = 0;
public:
	virtual skyVoid skyIGfxShader::Set ( skyVoid ) = 0;
	virtual skyVoid skyIGfxShader::Unset ( skyVoid ) = 0;
	virtual skyVoid skyIGfxShader::Compile ( skyVoid ) = 0;
};

class skyIGfxEffect
{
public:
	virtual skyIGfxEffect::~skyIGfxEffect() {}
public:
	virtual skyVoid skyIGfxEffect::SetConstantbuffer ( const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer ) = 0;
	virtual skyVoid skyIGfxEffect::SetTexture ( const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture ) = 0;
	virtual skyVoid skyIGfxEffect::SetSampler ( const skyUInt a_uiSlot, const skyIGfxSamplerState* a_pSampler ) = 0;	
public: 
	virtual skyVoid skyIGfxEffect::Apply ( ) = 0;
};

class skyIGfxFont
{
public:
	virtual skyIGfxFont::~skyIGfxFont() { }
public:
};

class skyIGfxSprite
{
public:
	virtual skyIGfxSprite::~skyIGfxSprite() { }
public:
	virtual skyVoid skyIGfxSprite::Draw ( skyVoid ) = 0;
};


class skyIGfxBlendState 
{
public:
	virtual skyIGfxBlendState::~skyIGfxBlendState() { }
public:
	virtual sGfxBlendDesc skyIGfxBlendState::GetDesc ( skyVoid ) = 0;
};

class skyIGfxDepthStencilState
{
public:
	virtual skyIGfxDepthStencilState::~skyIGfxDepthStencilState() { }
public:
	virtual sGfxDepthStencilDesc skyIGfxDepthStencilState::GetDesc ( skyVoid ) = 0;
};

class skyIGfxSamplerState
{
public:
	virtual skyIGfxSamplerState::~skyIGfxSamplerState() { }
public:
	virtual sGfxSamplerDesc skyIGfxSamplerState::GetDesc ( skyVoid ) = 0;
};

class skyIGfxRasterizerState
{
public:
	virtual skyIGfxRasterizerState::~skyIGfxRasterizerState() { }
public:
	virtual sGfxRasterizerDesc skyIGfxRasterizerState::GetDesc ( skyVoid ) = 0;
};

class skyIGfxStateManager
{
public:
	virtual skyIGfxStateManager::~skyIGfxStateManager() { }
public:
	virtual skyResult skyIGfxStateManager::SetBlendState ( skyIGfxBlendState* a_pNewState ) = 0;
	virtual skyResult skyIGfxStateManager::SetDepthStencilState ( skyIGfxDepthStencilState* a_pNewState ) = 0;
	virtual skyResult skyIGfxStateManager::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pNewState ) = 0;
	virtual skyResult skyIGfxStateManager::SetRasterizerState ( skyIGfxRasterizerState* a_pNewState ) = 0;
};

class skyIGfxPrimitive
{
public:
	virtual skyIGfxPrimitive::~skyIGfxPrimitive() { }
public:
	virtual skyVoid skyIGfxPrimitive::SetFillMode ( eGfxFillMode a_eMode ) = 0;
	virtual skyVoid skyIGfxPrimitive::EnableZWrite ( skyVoid ) = 0;
public:
	virtual skyVoid skyIGfxPrimitive::SetIndices ( skyIGfxIndexBuffer* a_pVertices ) = 0;
	virtual skyIGfxIndexBuffer* skyIGfxPrimitive::GetIndices ( skyVoid ) const = 0;
public:
	virtual skyVoid skyIGfxPrimitive::SetVertices ( skyIGfxVertexBuffer* a_pVertices ) = 0;
	virtual skyIGfxVertexBuffer* skyIGfxPrimitive::GetVertices ( skyVoid ) const = 0;

};

class skyIGfxRenderTarget
{
public:
	virtual skyIGfxRenderTarget::~skyIGfxRenderTarget() { }
public:
	virtual skyResult skyIGfxRenderTarget::CopyToTexture ( skyIGfxTexture* a_pTexture ) = 0;
	//virtual skyResult skyIGfxRenderTarget::SetBaseTexture ( skyIGfxTexture* a_pTexture ) = 0;
	virtual skyIGfxTexture* skyIGfxRenderTarget::GetBaseTexture ( skyVoid ) = 0;
};

class skyIGfxResourceManager	
{
public:
	virtual skyIGfxResourceManager::~skyIGfxResourceManager() { }
public:
	virtual skyResult skyIGfxResourceManager::RegisterResource ( skyIGfxResource* a_pResource ) = 0;
	virtual skyResult skyIGfxResourceManager::UnregisterResource ( skyIGfxResource* a_pResource ) = 0;
};

class skyIGfxSwapChain
{
public:
	virtual skyIGfxSwapChain::~skyIGfxSwapChain() { }
public:
	virtual skyResult skyIGfxSwapChain::Present ( sGfxPresentDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxSwapChain::GetBackBuffer ( skyIGfxTexture** a_pTexture ) = 0;
};

class skyIGfxSystem
{
public:
	virtual skyIGfxSystem::~skyIGfxSystem() { }
public:
	virtual skyResult skyIGfxSystem::CreateDevice ( sGfxDeviceDesc& a_sDesc, skyIGfxDevice** a_pDevice ) = 0;
};

class skyIGfxDevice
{
public:
	virtual skyIGfxDevice::~skyIGfxDevice() { }
public:
	virtual skyResult skyIGfxDevice::CreateTexture ( skyIGfxTexture** a_pTexture, sGfxTextureDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, sGfxTextureDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxDevice::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, skyIGfxTexture* a_pTexture ) = 0;
	virtual skyResult skyIGfxDevice::CreateIndexBuffer ( skyIGfxIndexBuffer** a_pBuffer, sGfxIndexDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxDevice::CreateVertexBuffer ( skyIGfxVertexBuffer** a_pBuffer, sGfxVertexDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxDevice::CreateConstantBuffer ( skyIGfxConstantBuffer** a_pBuffer, sGfxConstantDesc& a_sDesc ) = 0;
	virtual skyResult skyIGfxDevice::CreatePrimitive ( skyIGfxPrimitive** a_pPrimitive ) = 0;
	virtual skyResult skyIGfxDevice::CreateShader ( skyIGfxShader** a_pShader, sGfxShaderDesc& a_sDesc ) = 0;

public:
	virtual skyResult skyIGfxDevice::SetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget* a_pTarget, skyBool a_bUseDepthStencil = true ) = 0;
	virtual skyResult skyIGfxDevice::GetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget** a_pTarget ) = 0;
	virtual skyResult skyIGfxDevice::ClearRenderTarget ( skyUInt a_uiIndex, sGfxColor& a_sColor ) = 0;
	virtual skyResult skyIGfxDevice::ResetRenderTarget ( skyUInt a_uiIndex ) = 0;
	virtual skyResult skyIGfxDevice::ResetRenderTargets ( skyVoid ) = 0;
public:
	virtual skyResult skyIGfxDevice::CreateBlendState ( sGfxBlendDesc a_sDesc, skyIGfxBlendState** a_pState ) = 0;
	virtual skyResult skyIGfxDevice::CreateDepthState ( sGfxDepthStencilDesc a_sDesc, skyIGfxDepthStencilState** a_pState ) = 0;
	virtual skyResult skyIGfxDevice::CreateRasterizerState ( sGfxRasterizerDesc a_sDesc, skyIGfxRasterizerState** a_pState ) = 0;
	virtual skyResult skyIGfxDevice::CreateSamplerState ( sGfxSamplerDesc a_sDesc, skyIGfxSamplerState** a_pState ) = 0;
	
	virtual skyResult skyIGfxDevice::SetBlendState ( skyIGfxBlendState* a_pState ) = 0;
	virtual skyResult skyIGfxDevice::SetDepthState ( skyIGfxDepthStencilState* a_pState ) = 0;
	virtual skyResult skyIGfxDevice::SetRasterizerState ( skyIGfxRasterizerState* a_pState ) = 0;
	virtual skyResult skyIGfxDevice::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pState ) = 0;
public:
	virtual skyResult skyIGfxDevice::SetIndexBuffer ( skyIGfxIndexBuffer* a_pBuffer ) = 0;
	virtual skyResult skyIGfxDevice::SetVertexBuffer ( skyIGfxVertexBuffer* a_pBuffer, skyUInt a_u32Offset ) = 0;
public:
	virtual skyVoid skyIGfxDevice::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer ) = 0;
	virtual skyVoid skyIGfxDevice::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture ) = 0;
public:
	virtual skyResult skyIGfxDevice::SetDepthBuffer ( skyIGfxDepthBuffer* a_pBuffer) = 0;
	virtual skyIGfxDepthBuffer* skyIGfxDevice::GetDepthBuffer ( ) const = 0;
	virtual skyVoid skyIGfxDevice::ClearDepthBuffer ( ) = 0;
public:
	virtual skyVoid skyIGfxDevice::SetViewport ( const sGfxViewport& a_sViewport ) = 0;
	virtual sGfxViewport skyIGfxDevice::GetViewport ( skyVoid ) = 0;
public:
	virtual skyVoid skyIGfxDevice::SetSwapChain ( skyIGfxSwapChain* a_pChain ) = 0;
public:
	virtual skyResult skyIGfxDevice::GetBackBuffer ( skyIGfxTexture** a_pTexture ) = 0;
public:
	virtual skyVoid skyIGfxDevice::Draw ( skyIGfxPrimitive* a_pPrimitive ) = 0;
	virtual skyVoid skyIGfxDevice::Draw ( sGfxDrawDesc& a_sDesc ) = 0;
public:
	virtual skyVoid skyIGfxDevice::Present ( sGfxPresentDesc& a_sDesc ) = 0;
public:
	virtual skyVoid skyIGfxDevice::Resize ( skyVoid ) = 0;
};

class skyGfxViewport;
class skyGfxFrustum;