#pragma once

class skyD3D11Texture 
	: public skyIGfxTexture, public skyD3D11Resource

{
	// Construct stuff
public:
	static skyResult skyD3D11Texture::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxTextureDesc* a_sDesc, skyD3D11Texture** a_pTexture);
	static skyResult skyD3D11Texture::Spawn ( eLoadMode a_sLoadMode, skyD3D11GfxDevice* a_pDevice, sIOMemBlob* a_sBlob, skyD3D11Texture** a_pTexture);
	static skyResult skyD3D11Texture::Spawn ( skyD3D11GfxDevice* a_pDevice, ID3D11Texture2D* a_pTextureD3D11, skyD3D11Texture** a_pTexture);

	skyD3D11Texture::~skyD3D11Texture();
	
	// skyD3D11Resource
public:
	eGfxResourceType skyD3D11Texture::GetType ( skyVoid ) { return eGfxResourceType_Texture; }

	// skyIGfxTexture
public:
	virtual sGfxTextureDesc skyD3D11Texture::GetDesc ( skyVoid );
	// Copy
public:
	virtual skyResult skyD3D11Texture::CopyToCurrentRT ( skyVoid );
	virtual skyResult skyD3D11Texture::CopyTextureToTexture ( skyIGfxTexture* m_pSource );
	virtual skyResult skyD3D11Texture::CopyCurrentRT ( skyVoid );
	virtual skyResult skyD3D11Texture::CopyRTToTexture ( skyIGfxRenderTarget* a_pRT );
	// File Management
public:
	virtual skyResult skyD3D11Texture::SaveToFile ( skyString a_sFileName );
	virtual skyResult skyD3D11Texture::SaveToMemory ( skyVoid* a_pBuffer );
public:
	virtual skyVoid* skyD3D11Texture::GetData ( skyVoid );
public:
	virtual skyResult skyD3D11Texture::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData );
	virtual skyVoid skyD3D11Texture::Unlock ( skyUInt a_uiSubresource );
	
	// skyD3D11Texture
public:
	ID3D11ShaderResourceView* skyD3D11Texture::AsResourceView(skyVoid);
	ID3D11Texture2D* skyD3D11Texture::GetBaseTexture(skyVoid);
	// skyD3D11Texture
private:
	skyD3D11Texture::skyD3D11Texture(skyD3D11GfxDevice* a_pDevice, ID3D11Texture2D* a_pBaseTexture, ID3D11ShaderResourceView* a_pSRV);

private:
	ID3D11ShaderResourceView* m_pSRV;
	ID3D11Texture2D* m_pBaseTexture;
};