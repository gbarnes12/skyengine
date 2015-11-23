#include "stdafx.h"
#include "skyD3D11DepthBuffer.h"

skyResult skyD3D11DepthBuffer::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, skyD3D11DepthBuffer** a_pBuffer)
{
	ID3D11DepthStencilView* l_pBaseBuffer = nullptr;
	skyD3D11DepthBuffer* l_pBuffer = nullptr;
	skyD3D11Texture* l_pTexture = nullptr;
	sGfxTextureDesc l_sTextureDesc;
	D3D11_DEPTH_STENCIL_DESC l_sDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC l_sDSVDesc;
	skyResult hr;

	SKY_ZERO_MEM(&l_sTextureDesc, sizeof(sGfxTextureDesc));
	SKY_ZERO_MEM(&l_sDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	SKY_ZERO_MEM(&l_sDSVDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	// setup depth texture 
	l_sTextureDesc.m_uiWidth = skyConfig::g_windowWidth;
	l_sTextureDesc.m_uiHeight = skyConfig::g_windowHeight;
	l_sTextureDesc.m_uiMipLevels = 1;
	l_sTextureDesc.m_uiArraySize = 1;
	l_sTextureDesc.m_eFormat = eGfxDepthFormat_D24_UNORM_S8_UINT;
	l_sTextureDesc.m_sSample.m_uiCount = 1;
	l_sTextureDesc.m_sSample.m_uiQuality = 0;
	l_sTextureDesc.m_eUsage = eGfxUsage_Default;
	l_sTextureDesc.m_uiBindFlags = eGfxBindFlags_DepthStencil;
	l_sTextureDesc.m_uiCPUFlags= 0;
	l_sTextureDesc.m_uiMiscFlags = 0;

	hr = skyD3D11Texture::Spawn(a_pDevice, &l_sTextureDesc, &l_pTexture);
	if(hr != SKY_OK)
		return SKY_ERROR;

	// Set up the depth stencil view description.
	l_sDSVDesc.Format = static_cast<DXGI_FORMAT>(eGfxDepthFormat_D24_UNORM_S8_UINT);
	l_sDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	l_sDSVDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	if(FAILED( a_pDevice->m_pDevice->CreateDepthStencilView(l_pTexture->GetBaseTexture(), &l_sDSVDesc, &l_pBaseBuffer) ))
		return SKY_ERROR;

	l_pBuffer = SKY_NEW skyD3D11DepthBuffer(a_pDevice, l_pBaseBuffer, a_sDesc, l_pTexture);
	*a_pBuffer = l_pBuffer;

	return SKY_OK;
}


skyD3D11DepthBuffer::skyD3D11DepthBuffer( skyD3D11GfxDevice* a_pDevice, ID3D11DepthStencilView* a_pBaseBuffer, sGfxDepthStencilDesc a_sDesc, 
	skyIGfxTexture* a_pTexture)
	: m_pTexture(a_pTexture)
	, m_pBaseBuffer(a_pBaseBuffer)
	, m_sDesc(a_sDesc)
	, skyD3D11Resource(a_pDevice)
{

}

skyD3D11DepthBuffer::~skyD3D11DepthBuffer()
{
	SKY_RELEASE(m_pBaseBuffer);
	SKY_SAFE_DELETE(m_pTexture);
}