#include "stdafx.h"
#include "skyD3D11VertexBuffer.h"


skyResult skyD3D11ConstantBuffer::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxConstantDesc a_sDesc, skyD3D11ConstantBuffer** a_pBuffer )
{
	skyD3D11ConstantBuffer* pBuffer = nullptr;
	ID3D11Buffer* pBaseBuffer = nullptr;
	D3D11_BUFFER_DESC mBufferDesc;

	if(!a_pDevice) {
		SKY_PRINT_CONSOLE("error", "please provide valid pointers one of the three were null.", 0x01);
		return SKY_INVALID_POINTER;
	}

	SKY_ZERO_MEM(&mBufferDesc, sizeof(D3D11_BUFFER_DESC));

	mBufferDesc.Usage = static_cast<D3D11_USAGE>(a_sDesc.m_eUsage);
	mBufferDesc.CPUAccessFlags = static_cast<D3D11_CPU_ACCESS_FLAG>(a_sDesc.m_eCPUAccess);
	mBufferDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(a_sDesc.m_eBindFlags);
	mBufferDesc.ByteWidth = a_sDesc.m_uiSize * a_sDesc.m_uiCount;

	if ( a_sDesc.m_eUsage == eGfxUsage::eGfxUsage_Immutable) 
	{
		SKY_PRINT_CONSOLE("error", "can't use an immutable object without providing data please call different spawn method", 0x01);
		return SKY_ERROR;
	}

	if ( FAILED(a_pDevice->m_pDevice->CreateBuffer(&mBufferDesc, nullptr, &pBaseBuffer)) )
	{
		return SKY_ERROR;
	}

	pBuffer = SKY_NEW skyD3D11ConstantBuffer(a_pDevice, pBaseBuffer);

	*a_pBuffer = pBuffer;

	return SKY_OK;
}

skyResult skyD3D11ConstantBuffer::Spawn (skyD3D11GfxDevice* a_pDevice, skyVoid* a_pData 
										 , sGfxConstantDesc a_sDesc, skyD3D11ConstantBuffer** a_pBuffer )
{
	SKY_UNTESTED_METHOD("not tested yet! Spawn with data");

	skyD3D11ConstantBuffer* pBuffer = nullptr;
	ID3D11Buffer* pBaseBuffer = nullptr;
	D3D11_BUFFER_DESC mBufferDesc;
	D3D11_SUBRESOURCE_DATA mSubData;

	SKY_ZERO_MEM(&mBufferDesc, sizeof(D3D11_BUFFER_DESC));

	mBufferDesc.Usage = static_cast<D3D11_USAGE>(a_sDesc.m_eUsage);
	mBufferDesc.CPUAccessFlags = static_cast<D3D11_CPU_ACCESS_FLAG>(a_sDesc.m_eCPUAccess);
	mBufferDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(a_sDesc.m_eBindFlags);
	mBufferDesc.ByteWidth = a_sDesc.m_uiSize * a_sDesc.m_uiCount;

	// copy stuff 
	memcpy(&mSubData.pSysMem, a_pData, mBufferDesc.ByteWidth);  


	if ( FAILED(a_pDevice->m_pDevice->CreateBuffer(&mBufferDesc, &mSubData, &pBaseBuffer)) )
	{
		return SKY_ERROR;
	}

	SKY_TODO("add map and unmap copy mechanism!");

	pBuffer = SKY_NEW skyD3D11ConstantBuffer(a_pDevice, pBaseBuffer);

	*a_pBuffer = pBuffer;

	return SKY_OK;
}

skyD3D11ConstantBuffer::skyD3D11ConstantBuffer(skyD3D11GfxDevice* a_pDevice,  ID3D11Buffer* a_pBaseBuffer )
	: skyD3D11Resource(a_pDevice)
{
	this->m_pBaseBuffer = a_pBaseBuffer;
}

skyD3D11ConstantBuffer::~skyD3D11ConstantBuffer()
{
	SKY_RELEASE(this->m_pBaseBuffer);
}

sGfxConstantDesc skyD3D11ConstantBuffer::GetDesc ( skyVoid )
{
	D3D11_BUFFER_DESC desc;
	m_pBaseBuffer->GetDesc(&desc);

	sGfxConstantDesc outDesc;
	outDesc.m_eBindFlags = static_cast<eGfxBindFlags>(desc.BindFlags);
	outDesc.m_eCPUAccess = static_cast<eGfxCpuAccessFlags>(desc.CPUAccessFlags);
	outDesc.m_eUsage = static_cast<eGfxUsage>(desc.Usage);
	outDesc.m_uiSize = desc.StructureByteStride;
	outDesc.m_uiCount = desc.ByteWidth / desc.StructureByteStride;

	return outDesc;
}


skyVoid* skyD3D11ConstantBuffer::GetData ( skyVoid ) const
{
	return nullptr;
}

skyResult skyD3D11ConstantBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData )
{
	D3D11_MAPPED_SUBRESOURCE mappedResources;

	if ( FAILED ( m_pDevice->m_pContext->Map(m_pBaseBuffer, a_pData->m_uiSubresource, static_cast<D3D11_MAP>(a_eType), static_cast<D3D11_MAP_FLAG>(a_eFlags), &mappedResources) ) )
			return SKY_ERROR;

	a_pData->m_pData = mappedResources.pData;
	a_pData->m_uiRowPitch = mappedResources.RowPitch;
	a_pData->m_uiDepthPitch = mappedResources.DepthPitch;
	

	return SKY_OK;
}

void skyD3D11ConstantBuffer::Unlock ( skyUInt a_uiSubresource )
{
	m_pDevice->m_pContext->Unmap(this->m_pBaseBuffer, a_uiSubresource);
}
