#pragma once

class skyD3D11RenderTarget 
	: public skyIGfxRenderTarget, public skyD3D11Resource
{
public:
	static skyResult skyD3D11RenderTarget::Spawn ( skyD3D11GfxDevice* a_pDevice,sGfxTextureDesc a_sDesc, skyD3D11RenderTarget** a_pTarget );

	static skyResult skyD3D11RenderTarget::Spawn ( skyD3D11Texture* a_pTexture,skyD3D11GfxDevice* a_pDevice, skyD3D11RenderTarget** a_pTarget );

public:
	virtual eGfxResourceType skyD3D11RenderTarget::GetType ( skyVoid ) { return eGfxResourceType_RenderTarget; }
public:
	virtual skyD3D11RenderTarget::~skyD3D11RenderTarget();
public:
	virtual skyResult skyD3D11RenderTarget::CopyToTexture ( skyIGfxTexture* a_pTexture );
	virtual skyIGfxTexture* skyD3D11RenderTarget::GetBaseTexture ( skyVoid ) { return m_pTexture; }
public:
	ID3D11RenderTargetView* skyD3D11RenderTarget::AsView ( skyVoid ) { return m_pView; }

private:
	skyD3D11Texture* m_pTexture;
	ID3D11RenderTargetView* m_pView;

	skyD3D11RenderTarget::skyD3D11RenderTarget( skyD3D11GfxDevice* a_pDevice, skyD3D11Texture* a_pTexture, ID3D11RenderTargetView* a_pView );
};