#include "stdafx.h"
#include "skyD3D11RenderTarget.h"

skyResult skyD3D11RenderTarget::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxTextureDesc a_sDesc, skyD3D11RenderTarget** a_pTarget )
{
	ID3D11RenderTargetView* l_pView = nullptr;
	skyD3D11RenderTarget* l_pTarget = nullptr;
	skyD3D11Texture* l_pTexture = nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC l_sRenderTargetViewDesc;
	skyResult hr;

	hr = skyD3D11Texture::Spawn(a_pDevice, &a_sDesc, &l_pTexture);
	if(hr != SKY_OK)
		return hr;
	
	SKY_ZERO_MEM(&l_sRenderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	l_sRenderTargetViewDesc.Format = static_cast<DXGI_FORMAT>(a_sDesc.m_eFormat);
	l_sRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	l_sRenderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	HRESULT dxHr = a_pDevice->m_pDevice->CreateRenderTargetView(l_pTexture->GetBaseTexture(), &l_sRenderTargetViewDesc, &l_pView);
	if(FAILED(dxHr))
	{
		SKY_SAFE_DELETE(l_pTexture);
		return SKY_INVALID_POINTER;
	}


	l_pTarget = SKY_NEW skyD3D11RenderTarget(a_pDevice, l_pTexture, l_pView);
	*a_pTarget = l_pTarget;

	return SKY_OK;
}

skyResult skyD3D11RenderTarget::Spawn ( skyD3D11Texture* a_pTexture, skyD3D11GfxDevice* a_pDevice, skyD3D11RenderTarget** a_pTarget )
{
	ID3D11RenderTargetView* l_pView = nullptr;
	skyD3D11RenderTarget* l_pTarget = nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC l_sRenderTargetViewDesc;
	sGfxTextureDesc l_sDesc = a_pTexture->GetDesc();

	SKY_ZERO_MEM(&l_sRenderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	l_sRenderTargetViewDesc.Format = static_cast<DXGI_FORMAT>(l_sDesc.m_eFormat);
	l_sRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	l_sRenderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	HRESULT dxHr = a_pDevice->m_pDevice->CreateRenderTargetView(a_pTexture->GetBaseTexture(), &l_sRenderTargetViewDesc, &l_pView);
	if(FAILED(dxHr))
	{
		return SKY_INVALID_POINTER;
	}


	l_pTarget = SKY_NEW skyD3D11RenderTarget(a_pDevice, a_pTexture, l_pView);
	*a_pTarget = l_pTarget;

	return SKY_OK;
}


skyD3D11RenderTarget::skyD3D11RenderTarget( skyD3D11GfxDevice* a_pDevice, skyD3D11Texture* a_pTexture, ID3D11RenderTargetView* a_pView )
	: skyD3D11Resource(a_pDevice)
	, m_pTexture (a_pTexture)
	, m_pView(a_pView)
{
}

skyD3D11RenderTarget::~skyD3D11RenderTarget()
{
}

skyResult skyD3D11RenderTarget::CopyToTexture ( skyIGfxTexture* a_pTexture )
{
	return SKY_NOT_IMPLEMENTED;
}



