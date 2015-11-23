#include "stdafx.h"
#include "skyD3D11GfxSwapChain.h"


skyResult skyD3D11GfxSwapChain::Spawn (  skyD3D11GfxDevice* a_pDevice, IDXGISwapChain* a_pSwapChain, skyD3D11GfxSwapChain** a_pChain)
{
	skyD3D11GfxSwapChain* l_pChain = nullptr;

	if(!a_pSwapChain)
		return SKY_INVALID_POINTER;
	
	l_pChain = SKY_NEW skyD3D11GfxSwapChain(a_pDevice, a_pSwapChain);
	*a_pChain = l_pChain;

	return SKY_OK;
}

skyD3D11GfxSwapChain::skyD3D11GfxSwapChain( skyD3D11GfxDevice* a_pDevice, IDXGISwapChain* a_pSwapChain)
	: m_pSwapChain(a_pSwapChain)
	, m_pDevice(a_pDevice)
{
}

skyD3D11GfxSwapChain::~skyD3D11GfxSwapChain()
{
	SKY_RELEASE(m_pSwapChain);
}

skyResult skyD3D11GfxSwapChain::GetBackBuffer ( skyIGfxTexture** a_pTexture )
{
	skyD3D11Texture* pTexture = nullptr;
	ID3D11Texture2D* pD3D11Texture = nullptr;
	skyResult hr;

	if( FAILED ( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pD3D11Texture ) ) ) 
		return SKY_INVALID_POINTER;

	SKY_VR(skyD3D11Texture::Spawn(m_pDevice, pD3D11Texture, &pTexture));
	*a_pTexture = pTexture;

	return SKY_OK;
}

skyResult skyD3D11GfxSwapChain::Present ( sGfxPresentDesc& a_sDesc )
{
	m_pSwapChain->Present(a_sDesc.m_uiSyncInterval, a_sDesc.m_uiFlags);

	return SKY_OK;
}

