#pragma once

class skyD3D11GfxSwapChain 
	: public skyIGfxSwapChain
{
public:
	static skyResult skyD3D11GfxSwapChain::Spawn ( skyD3D11GfxDevice* a_pDevice, IDXGISwapChain* a_pSwapChain, skyD3D11GfxSwapChain** a_pChain);

	skyD3D11GfxSwapChain::~skyD3D11GfxSwapChain();

public:
	virtual skyResult skyD3D11GfxSwapChain::Present ( sGfxPresentDesc& a_sDesc );
	IDXGISwapChain* skyD3D11GfxSwapChain::GetBaseSwapChain ( skyVoid ) { return m_pSwapChain; }
public:
	skyResult skyD3D11GfxSwapChain::GetBackBuffer ( skyIGfxTexture** a_pTexture );
private:

	IDXGISwapChain* m_pSwapChain;
	skyD3D11GfxDevice* m_pDevice;

	skyD3D11GfxSwapChain::skyD3D11GfxSwapChain( skyD3D11GfxDevice* a_pDevice, IDXGISwapChain* a_pSwapChain);
};