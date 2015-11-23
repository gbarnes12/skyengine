#pragma once 

class skyGfxManager 
{
public:
	static skyResult skyGfxManager::Initialize ( skyVoid );
	static skyResult skyGfxManager::Shutdown ( skyVoid );

	static skyIWindow* skyGfxManager::Window ( skyVoid );

	// skyIGfxDevice 
public:
	static skyResult skyGfxManager::CreateTexture ( skyIGfxTexture** a_pTexture, sGfxTextureDesc& a_sDesc );
	static skyResult skyGfxManager::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, sGfxTextureDesc& a_sDesc );
	static skyResult skyGfxManager::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, skyIGfxTexture* a_pTexture );
	static skyResult skyGfxManager::CreateIndexBuffer ( skyIGfxIndexBuffer** a_pBuffer, sGfxIndexDesc& a_sDesc );
	static skyResult skyGfxManager::CreateVertexBuffer ( skyIGfxVertexBuffer** a_pBuffer, sGfxVertexDesc& a_sDesc );
	static skyResult skyGfxManager::CreateConstantBuffer ( skyIGfxConstantBuffer** a_pBuffer, sGfxConstantDesc& a_sDesc );
	static skyResult skyGfxManager::CreatePrimitive ( skyIGfxPrimitive** a_pPrimitive );
	static skyResult skyGfxManager::CreateShader ( skyIGfxShader** a_pShader, sGfxShaderDesc& a_sDesc );

public:
	static skyResult skyGfxManager::SetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget* a_pTarget, skyBool a_bUseDepthStencil = true );
	static skyResult skyGfxManager::GetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget** a_pTarget );
	static skyResult skyGfxManager::ClearRenderTarget ( skyUInt a_uiIndex, sGfxColor& a_sColor );
	static skyResult skyGfxManager::ResetRenderTarget ( skyUInt a_uiIndex );
	static skyResult skyGfxManager::ResetRenderTargets ( skyVoid );
public:
	static skyResult skyGfxManager::CreateBlendState ( sGfxBlendDesc a_sDesc, skyIGfxBlendState** a_pState );
	static skyResult skyGfxManager::CreateDepthState ( sGfxDepthStencilDesc a_sDesc, skyIGfxDepthStencilState** a_pState );
	static skyResult skyGfxManager::CreateRasterizerState ( sGfxRasterizerDesc a_sDesc, skyIGfxRasterizerState** a_pState );
	static skyResult skyGfxManager::CreateSamplerState ( sGfxSamplerDesc a_sDesc, skyIGfxSamplerState** a_pState );
	
	static skyResult skyGfxManager::SetBlendState ( skyIGfxBlendState* a_pState );
	static skyResult skyGfxManager::SetDepthState ( skyIGfxDepthStencilState* a_pState );
	static skyResult skyGfxManager::SetRasterizerState ( skyIGfxRasterizerState* a_pState );
	static skyResult skyGfxManager::SetSamplerState ( eGfxShaderType a_eType, const skyUInt a_uiSlot, skyIGfxSamplerState* a_pState );
public:
	static skyVoid skyGfxManager::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer );
	static skyVoid skyGfxManager::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture );
public:
	static skyResult skyGfxManager::SetIndexBuffer ( skyIGfxIndexBuffer* a_pBuffer );
	static skyResult skyGfxManager::SetVertexBuffer ( skyIGfxVertexBuffer* a_pBuffer, skyUInt a_u32Offset );
public:
	static skyIGfxTexture* skyGfxManager::GetBackBuffer ( skyVoid );
	static skyIGfxRenderTarget* skyGfxManager::BackBufferRT ( skyVoid );
	static skyIGfxConstantBuffer* skyGfxManager::ConstantMatrixBuffer ( skyVoid );
public:
	static skyVoid skyGfxManager::SetViewport ( const sGfxViewport& a_sViewport );
	static sGfxViewport skyGfxManager::GetViewport ( skyVoid );
public:
	static skyVoid skyGfxManager::Draw ( skyIGfxPrimitive* a_pPrimitive );
	static skyVoid skyGfxManager::Draw ( sGfxDrawDesc& a_sDesc );
public:
	static skyVoid skyGfxManager::Present ( sGfxPresentDesc& a_sDesc );
public:
	static skyVoid skyGfxManager::Resize ( skyVoid );
};