#include "stdafx.h"
#include "skyGfxInstance.h"
#include "skyGfxManager.h"

static skyGfxInstance mInstance;

skyResult skyGfxManager::Initialize ( skyVoid )
{
	return mInstance.Initialize();
}

skyResult skyGfxManager::Shutdown ( skyVoid )
{
	return mInstance.Shutdown();
}


skyIWindow* skyGfxManager::Window ( skyVoid )
{
	return mInstance.Window();
}

skyResult skyGfxManager::CreateTexture ( skyIGfxTexture** a_pTexture, sGfxTextureDesc& a_sDesc )
{
	return mInstance.Device()->CreateTexture(a_pTexture, a_sDesc);
}

skyResult skyGfxManager::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, sGfxTextureDesc& a_sDesc )
{
	return mInstance.Device()->CreateRenderTarget(a_pRT, a_sDesc);
}

skyResult skyGfxManager::CreateRenderTarget ( skyIGfxRenderTarget** a_pRT, skyIGfxTexture* a_pTexture )
{
	return mInstance.Device()->CreateRenderTarget(a_pRT, a_pTexture);
}

skyResult skyGfxManager::CreateIndexBuffer ( skyIGfxIndexBuffer** a_pBuffer, sGfxIndexDesc& a_sDesc )
{
	return mInstance.Device()->CreateIndexBuffer(a_pBuffer, a_sDesc);
}

skyResult skyGfxManager::CreateVertexBuffer ( skyIGfxVertexBuffer** a_pBuffer, sGfxVertexDesc& a_sDesc )
{
	return mInstance.Device()->CreateVertexBuffer(a_pBuffer, a_sDesc);
}

skyResult skyGfxManager::CreateConstantBuffer ( skyIGfxConstantBuffer** a_pBuffer, sGfxConstantDesc& a_sDesc )
{
	return mInstance.Device()->CreateConstantBuffer(a_pBuffer, a_sDesc);
}

skyResult skyGfxManager::CreatePrimitive ( skyIGfxPrimitive** a_pPrimitive )
{
	return mInstance.Device()->CreatePrimitive(a_pPrimitive);
}

skyResult skyGfxManager::CreateShader ( skyIGfxShader** a_pShader, sGfxShaderDesc& a_sDesc )
{
	return mInstance.Device()->CreateShader(a_pShader, a_sDesc);
}
//
// -----------------------------------------------------------------------------------------------------------
//
skyResult skyGfxManager::SetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget* a_pTarget, skyBool a_bUseDepthStencil )
{
	return mInstance.Device()->SetRenderTarget(a_uiIndex, a_pTarget, a_bUseDepthStencil);
}

skyResult skyGfxManager::GetRenderTarget ( skyUInt a_uiIndex, skyIGfxRenderTarget** a_pTarget )
{
	return mInstance.Device()->GetRenderTarget(a_uiIndex, a_pTarget);
}

skyResult skyGfxManager::ClearRenderTarget ( skyUInt a_uiIndex, sGfxColor& a_sColor )
{
	return mInstance.Device()->ClearRenderTarget(a_uiIndex, a_sColor);
}

skyResult skyGfxManager::ResetRenderTarget ( skyUInt a_uiIndex )
{
	return mInstance.Device()->ResetRenderTarget(a_uiIndex);
}

skyResult skyGfxManager::ResetRenderTargets ( skyVoid )
{
	return mInstance.Device()->ResetRenderTargets();
}
//
// -------------------------------------------------------------------------------
// 
 skyResult skyGfxManager::CreateBlendState ( sGfxBlendDesc a_sDesc, skyIGfxBlendState** a_pState )
{
	return mInstance.Device()->CreateBlendState(a_sDesc, a_pState);
}

skyResult skyGfxManager::CreateDepthState ( sGfxDepthStencilDesc a_sDesc, skyIGfxDepthStencilState** a_pState )
{
	return mInstance.Device()->CreateDepthState(a_sDesc, a_pState);
}

skyResult skyGfxManager::CreateRasterizerState ( sGfxRasterizerDesc a_sDesc, skyIGfxRasterizerState** a_pState )
{
	return mInstance.Device()->CreateRasterizerState(a_sDesc, a_pState);
}

skyResult skyGfxManager::CreateSamplerState ( sGfxSamplerDesc a_sDesc, skyIGfxSamplerState** a_pState )
{
	return mInstance.Device()->CreateSamplerState(a_sDesc, a_pState);
}
	
skyResult skyGfxManager::SetBlendState ( skyIGfxBlendState* a_pState )
{
	return mInstance.Device()->SetBlendState(a_pState);
}

skyResult skyGfxManager::SetDepthState ( skyIGfxDepthStencilState* a_pState )
{
	return mInstance.Device()->SetDepthState( a_pState);
}

skyResult skyGfxManager::SetRasterizerState ( skyIGfxRasterizerState* a_pState )
{
	return mInstance.Device()->SetRasterizerState(a_pState);
}

skyResult skyGfxManager::SetSamplerState (eGfxShaderType a_eType, const skyUInt a_uiSlot,  skyIGfxSamplerState* a_pState )
{
	return mInstance.Device()->SetSamplerState(a_eType, a_uiSlot, a_pState);
}

skyVoid skyGfxManager::SetConstantbuffer ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxConstantBuffer* a_pBuffer )
{
	return mInstance.Device()->SetConstantbuffer(a_eType, a_uiSlot, a_pBuffer);
}

skyVoid skyGfxManager::SetTexture ( eGfxShaderType a_eType, const skyUInt a_uiSlot, const skyIGfxTexture* a_pTexture )
{
	return mInstance.Device()->SetTexture(a_eType, a_uiSlot, a_pTexture);
}

//
// -------------------------------------------------------------------------------
// 

skyResult skyGfxManager::SetIndexBuffer ( skyIGfxIndexBuffer* a_pBuffer )
{
	return mInstance.Device()->SetIndexBuffer(a_pBuffer);
}

skyResult skyGfxManager::SetVertexBuffer ( skyIGfxVertexBuffer* a_pBuffer, skyUInt a_u32Offset )
{
	return mInstance.Device()->SetVertexBuffer(a_pBuffer, a_u32Offset);
}

skyIGfxTexture* skyGfxManager::GetBackBuffer ( skyVoid )
{
	return mInstance.BackBuffer();
}

skyIGfxRenderTarget* skyGfxManager::BackBufferRT ( skyVoid )
{
	return mInstance.BackBufferRT();
}


skyIGfxConstantBuffer* skyGfxManager::ConstantMatrixBuffer ( skyVoid )
{
	return mInstance.ConstantMatrixBuffer();
}

//
// -------------------------------------------------------------------------------
// 
skyVoid skyGfxManager::SetViewport ( const sGfxViewport& a_sViewport )
{
	mInstance.Device()->SetViewport(a_sViewport);
}

sGfxViewport skyGfxManager::GetViewport ( skyVoid )
{
	return mInstance.Device()->GetViewport();
}

//
// -------------------------------------------------------------------------------
// 

skyVoid skyGfxManager::Draw ( skyIGfxPrimitive* a_pPrimitive )
{
	mInstance.Device()->Draw(a_pPrimitive);
}

skyVoid skyGfxManager::Draw ( sGfxDrawDesc& a_sDesc )
{
	mInstance.Device()->Draw(a_sDesc);
}

skyVoid skyGfxManager::Present ( sGfxPresentDesc& a_sDesc )
{
	mInstance.Device()->Present(a_sDesc);
}

skyVoid skyGfxManager::Resize ( skyVoid )
{
	mInstance.Device()->Resize();
}