#pragma once

class skyD3D11VertexBuffer 
	: public skyIGfxVertexBuffer,public skyD3D11Resource
{
public:
	static skyResult skyD3D11VertexBuffer::Spawn (  skyD3D11GfxDevice* a_pDevice, sGfxVertexDesc a_sDesc, skyD3D11VertexBuffer** a_pBuffer );
	static skyResult skyD3D11VertexBuffer::Spawn (  skyD3D11GfxDevice* a_pDevice, skyVoid* a_pData, sGfxVertexDesc a_sDesc, skyD3D11VertexBuffer** a_pBuffer );
	skyD3D11VertexBuffer::~skyD3D11VertexBuffer();

public:
	virtual eGfxResourceType skyD3D11VertexBuffer::GetType ( skyVoid ) { return eGfxResourceType_VertexBuffer; }
	virtual sGfxVertexDesc skyD3D11VertexBuffer::GetDesc ( skyVoid );
public:
	virtual skyVoid* skyD3D11VertexBuffer::GetData ( skyVoid ) const;
public:
	virtual skyVoid skyD3D11VertexBuffer::SetStride( skyUInt a_u32Stride );
	virtual skyUInt skyD3D11VertexBuffer::GetStride( skyVoid );
public:
	virtual skyVoid skyD3D11VertexBuffer::SetElementCount( skyUInt a_u32Count );
	virtual skyUInt skyD3D11VertexBuffer::GetElementCount( skyVoid );
public:
	virtual skyResult skyD3D11VertexBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData  );
	virtual skyVoid skyD3D11VertexBuffer::Unlock ( skyUInt a_uiSubresource );

// D3D11 Stuff
public:
	ID3D11Buffer* GetBaseBuffer() { return this->m_pBaseBuffer; }

private: 
	ID3D11Buffer* m_pBaseBuffer;
	skyUInt m_u32Stride;
	skyUInt m_u32ElementCount;

	skyD3D11VertexBuffer::skyD3D11VertexBuffer(  skyD3D11GfxDevice* a_pDevice, ID3D11Buffer* a_pBaseBuffer);
};