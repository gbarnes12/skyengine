#include "stdafx.h"
#include "skyD3D11Texture.h"


skyResult skyD3D11Texture::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxTextureDesc* a_sDesc, skyD3D11Texture** a_pTexture)
{
	skyD3D11Texture* pTexture = nullptr;
	ID3D11Texture2D* pBaseTexture = nullptr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	D3D11_TEXTURE2D_DESC mTextureDesc;

	if(!a_pDevice) {
		SKY_PRINT_CONSOLE("error", "please provide valid pointers one of the three were null.", 0x01);
		return SKY_INVALID_POINTER;
	}

	SKY_ZERO_MEM(&mTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	mTextureDesc.Format = static_cast<DXGI_FORMAT>(a_sDesc->m_eFormat);
	mTextureDesc.Usage = static_cast<D3D11_USAGE>(a_sDesc->m_eUsage);
	mTextureDesc.Width = a_sDesc->m_uiWidth;
	mTextureDesc.Height = a_sDesc->m_uiHeight;
	mTextureDesc.MipLevels = a_sDesc->m_uiMipLevels;
	mTextureDesc.CPUAccessFlags = static_cast<D3D11_CPU_ACCESS_FLAG>(a_sDesc->m_uiCPUFlags);
	mTextureDesc.ArraySize = a_sDesc->m_uiArraySize;
	mTextureDesc.MiscFlags = static_cast<D3D11_MAP_FLAG>(a_sDesc->m_uiMiscFlags);
	mTextureDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(a_sDesc->m_uiBindFlags);
	mTextureDesc.SampleDesc.Count = a_sDesc->m_sSample.m_uiCount;
	mTextureDesc.SampleDesc.Quality = a_sDesc->m_sSample.m_uiQuality;

	if ( a_sDesc->m_eUsage == eGfxUsage::eGfxUsage_Immutable) 
	{
		SKY_PRINT_CONSOLE("error", "can't use an immutable object without providing data please call different spawn method", 0x01);
		return SKY_ERROR;
	}

	if ( FAILED(a_pDevice->m_pDevice->CreateTexture2D(&mTextureDesc, nullptr, &pBaseTexture)) )
	{
		return SKY_ERROR;
	}

	// when we use the depth buffer format don't use a shader resource view!
	if(a_sDesc->m_eFormat != eGfxDepthFormat_D24_UNORM_S8_UINT && SKY_HAS_FLAG(a_sDesc->m_uiBindFlags, eGfxBindFlags_ShaderResource))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC l_sShaderViewDesc;
		SKY_ZERO_MEM(&l_sShaderViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		l_sShaderViewDesc.Format = static_cast<DXGI_FORMAT>(a_sDesc->m_eFormat);
		l_sShaderViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		l_sShaderViewDesc.Texture2D.MostDetailedMip = mTextureDesc.MipLevels-1; 
		l_sShaderViewDesc.Texture2D.MipLevels = mTextureDesc.MipLevels;
		if ( FAILED(a_pDevice->m_pDevice->CreateShaderResourceView(pBaseTexture, &l_sShaderViewDesc, &pSRV)) )
		{
			return SKY_ERROR;
		}
	}

	pTexture = SKY_NEW skyD3D11Texture(a_pDevice, pBaseTexture, pSRV);

	*a_pTexture = pTexture;

	return SKY_OK;
}


skyResult skyD3D11Texture::Spawn ( eLoadMode a_sLoadMode, skyD3D11GfxDevice* a_pDevice, sIOMemBlob* a_sBlob, skyD3D11Texture** a_pTexture)
{
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(*a_sBlob);
	skyD3D11Texture* pTexture = nullptr;
	ID3D11Texture2D* pBaseTexture = nullptr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	D3D11_TEXTURE2D_DESC mTextureDesc;
	SKY_ZERO_MEM(&mTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	if ( FAILED(D3DX11CreateTextureFromMemory(a_pDevice->m_pDevice, pContent, a_sBlob->m_uiBufferSize, NULL, NULL, (ID3D11Resource**)&pBaseTexture, NULL)) )
	{
		return SKY_ERROR;
	}

	if ( FAILED(D3DX11CreateShaderResourceViewFromMemory(a_pDevice->m_pDevice, pContent, a_sBlob->m_uiBufferSize, NULL, NULL, &pSRV, NULL)))
	{
		return SKY_ERROR;
	}

	pTexture = SKY_NEW skyD3D11Texture(a_pDevice, pBaseTexture, pSRV);

	*a_pTexture = pTexture;

	return SKY_OK;
}

skyResult skyD3D11Texture::Spawn ( skyD3D11GfxDevice* a_pDevice, ID3D11Texture2D* a_pTextureD3D11, skyD3D11Texture** a_pTexture)
{
	skyD3D11Texture* pTexture = nullptr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	D3D11_TEXTURE2D_DESC mTextureDesc;

	if( !a_pDevice || !a_pTextureD3D11 ) {
		SKY_PRINT_CONSOLE("error", "please provide valid pointers one of the three were null.", 0x01);
		return SKY_INVALID_POINTER;
	}

	// retrieve the description!
	a_pTextureD3D11->GetDesc(&mTextureDesc);



	if(mTextureDesc.Format != static_cast<DXGI_FORMAT>(eGfxDepthFormat_D24_UNORM_S8_UINT) && SKY_HAS_FLAG(mTextureDesc.BindFlags, D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC l_sShaderViewDesc;
		SKY_ZERO_MEM(&l_sShaderViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		l_sShaderViewDesc.Format = mTextureDesc.Format;
		l_sShaderViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;

		if ( FAILED(a_pDevice->m_pDevice->CreateShaderResourceView(a_pTextureD3D11, &l_sShaderViewDesc, &pSRV)) )
		{
			return SKY_ERROR;
		}
	}

	pTexture = SKY_NEW skyD3D11Texture(a_pDevice, a_pTextureD3D11, pSRV);

	*a_pTexture = pTexture;

	return SKY_OK;
}

skyD3D11Texture::skyD3D11Texture(skyD3D11GfxDevice* a_pDevice, ID3D11Texture2D* a_pBaseTexture, ID3D11ShaderResourceView* a_pSRV)
	: skyD3D11Resource(a_pDevice)
{
	this->m_pBaseTexture = a_pBaseTexture;
	this->m_pSRV = a_pSRV;
}

skyD3D11Texture::~skyD3D11Texture()
{
	SKY_RELEASE(this->m_pSRV);
	SKY_RELEASE(this->m_pBaseTexture);
}

SKY_TODO("still need to add sampler desc to output desc");
sGfxTextureDesc skyD3D11Texture::GetDesc ( skyVoid )
{

	D3D11_TEXTURE2D_DESC l_sDesc;
	sGfxTextureDesc l_sDescOut;

	this->m_pBaseTexture->GetDesc(&l_sDesc);

	l_sDescOut.m_eFormat = static_cast<eGfxFormat>(l_sDesc.Format);
	l_sDescOut.m_eUsage = static_cast<eGfxUsage>(l_sDesc.Usage);
	l_sDescOut.m_uiWidth = l_sDesc.Width;
	l_sDescOut.m_uiHeight = l_sDesc.Height;
	l_sDescOut.m_uiMipLevels = l_sDesc.MipLevels;
	l_sDescOut.m_uiCPUFlags = static_cast<eGfxCpuAccessFlags>(l_sDesc.CPUAccessFlags);
	l_sDescOut.m_uiArraySize = l_sDesc.ArraySize;
	l_sDescOut.m_uiMiscFlags = static_cast<eGfxMapFlags>(l_sDesc.MiscFlags);
	l_sDescOut.m_uiBindFlags = static_cast<eGfxBindFlags>(l_sDesc.BindFlags);


	return l_sDescOut;
}

skyResult skyD3D11Texture::CopyToCurrentRT ( skyVoid )
{
	SKY_UNTESTED_METHOD("not yet implemented");
	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11Texture::CopyTextureToTexture ( skyIGfxTexture* m_pSource )
{
	SKY_UNTESTED_METHOD("not yet implemented");
	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11Texture::CopyCurrentRT ( skyVoid )
{
	SKY_UNTESTED_METHOD("not yet implemented");
	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11Texture::CopyRTToTexture ( skyIGfxRenderTarget* a_pRT )
{
	SKY_UNTESTED_METHOD("not yet implemented");
	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11Texture::SaveToFile ( skyString a_sFileName )
{
	SKY_UNTESTED_METHOD("not yet implemented");
	return SKY_NOT_SUPPORTED;
}

skyResult skyD3D11Texture::SaveToMemory ( skyVoid* a_pBuffer )
{
	a_pBuffer = this->GetData();

	if(!a_pBuffer)
		return SKY_INVALID_POINTER;

	return SKY_OK;
}

skyVoid* skyD3D11Texture::GetData ( skyVoid ) 
{
	skyVoid* o_pBuffer = nullptr;
	sGfxLockedBuffer l_pBuffer;
	sGfxTextureDesc l_sDesc = this->GetDesc();
	skyResult hr;

	SKY_ZERO_MEM(&l_pBuffer, sizeof(sGfxLockedBuffer));
	hr = this->Lock(eGfxMapType_Read, eGfxMapFlag_DoNotWait, &l_pBuffer);

	if(hr != SKY_OK)
		return o_pBuffer;

	memcpy(o_pBuffer, l_pBuffer.m_pData, l_sDesc.m_uiArraySize);

	this->Unlock(l_pBuffer.m_uiSubresource);

	return o_pBuffer;
}

skyResult skyD3D11Texture::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData )
{
	D3D11_MAPPED_SUBRESOURCE mappedResources;

	if ( FAILED ( m_pDevice->m_pContext->Map(m_pBaseTexture, a_pData->m_uiSubresource, static_cast<D3D11_MAP>(a_eType), static_cast<D3D11_MAP_FLAG>(a_eFlags), &mappedResources) ) )
			return SKY_ERROR;

	a_pData->m_pData = mappedResources.pData;
	a_pData->m_uiRowPitch = mappedResources.RowPitch;
	a_pData->m_uiDepthPitch = mappedResources.DepthPitch;
	

	return SKY_OK;
}

skyVoid skyD3D11Texture::Unlock ( skyUInt a_uiSubresource )
{
	m_pDevice->m_pContext->Unmap(this->m_pBaseTexture, a_uiSubresource);
}

ID3D11ShaderResourceView* skyD3D11Texture::AsResourceView(skyVoid)
{
	return this->m_pSRV;
}

ID3D11Texture2D* skyD3D11Texture::GetBaseTexture(skyVoid)
{
	return this->m_pBaseTexture;
}

