#pragma once

class skyD3D11ConstantBuffer 
	: public skyIGfxConstantBuffer, public skyD3D11Resource
{
public:
	static skyResult skyD3D11ConstantBuffer::Spawn ( skyD3D11GfxDevice* a_pDevice, sGfxConstantDesc a_sDesc, skyD3D11ConstantBuffer** a_pBuffer );

	static skyResult skyD3D11ConstantBuffer::Spawn ( skyD3D11GfxDevice* a_pDevice, skyVoid* a_pData, sGfxConstantDesc a_sDesc, skyD3D11ConstantBuffer** a_pBuffer );

	skyD3D11ConstantBuffer::~skyD3D11ConstantBuffer();

public:
	virtual eGfxResourceType skyD3D11ConstantBuffer::GetType ( skyVoid ) { return eGfxResourceType_ConstantBuffer; }
	virtual sGfxConstantDesc skyD3D11ConstantBuffer::GetDesc ( skyVoid );
public:
	virtual skyVoid* skyD3D11ConstantBuffer::GetData ( skyVoid ) const;
public:
	virtual skyResult skyD3D11ConstantBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData  );
	virtual skyVoid skyD3D11ConstantBuffer::Unlock ( skyUInt a_uiSubresource );

// D3D11 Stuff
public:
	ID3D11Buffer* GetBaseBuffer() { return this->m_pBaseBuffer; }

private: 
	ID3D11Buffer* m_pBaseBuffer;

	skyD3D11ConstantBuffer::skyD3D11ConstantBuffer( skyD3D11GfxDevice* a_pDevice, ID3D11Buffer* a_pBaseBuffer );
};