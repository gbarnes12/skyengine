#pragma once

class skyD3D11DepthBuffer 
	: public skyIGfxDepthBuffer, public skyD3D11Resource
{
public:
	static skyResult skyD3D11DepthBuffer::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxDepthStencilDesc a_sDesc, skyD3D11DepthBuffer** a_pBuffer);

	skyD3D11DepthBuffer::~skyD3D11DepthBuffer();

	virtual eGfxResourceType skyD3D11DepthBuffer::GetType ( skyVoid ) { return eGfxResourceType_DepthBuffer; }

public:
	virtual sGfxDepthStencilDesc skyD3D11DepthBuffer::GetDesc ( skyVoid ) { return m_sDesc; }
	virtual skyIGfxTexture* skyD3D11DepthBuffer::GetDepthTexture ( skyVoid ) { return m_pTexture; }
	ID3D11DepthStencilView* skyD3D11DepthBuffer::AsView ( skyVoid ) { return m_pBaseBuffer; }
private:
	skyIGfxTexture* m_pTexture;
	ID3D11DepthStencilView* m_pBaseBuffer;
	sGfxDepthStencilDesc m_sDesc;

	skyD3D11DepthBuffer::skyD3D11DepthBuffer( skyD3D11GfxDevice* a_pDevice,ID3D11DepthStencilView* a_pBaseBuffer, 
		sGfxDepthStencilDesc a_sDesc, skyIGfxTexture* a_pTexture);
};