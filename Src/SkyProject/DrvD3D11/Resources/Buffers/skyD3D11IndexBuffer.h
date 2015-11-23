#pragma once

class skyD3D11IndexBuffer 
	: public skyIGfxIndexBuffer, public skyD3D11Resource
{
public:
	static skyResult skyD3D11IndexBuffer::Spawn (  skyD3D11GfxDevice* a_pDevice, sGfxIndexDesc a_sDesc, skyD3D11IndexBuffer** a_pBuffer );
	static skyResult skyD3D11IndexBuffer::Spawn (  skyD3D11GfxDevice* a_pDevice, skyVoid* a_pData, sGfxIndexDesc a_sDesc, skyD3D11IndexBuffer** a_pBuffer );
	skyD3D11IndexBuffer::~skyD3D11IndexBuffer();

public:
	virtual eGfxResourceType skyD3D11IndexBuffer::GetType ( skyVoid ) { return eGfxResourceType_IndexBuffer; }
	virtual sGfxIndexDesc skyD3D11IndexBuffer::GetDesc ( skyVoid );
public:
	virtual skyVoid* skyD3D11IndexBuffer::GetData ( skyVoid ) const;
public:
	virtual skyResult skyD3D11IndexBuffer::Lock ( eGfxMapTypes a_eType, eGfxMapFlags a_eFlags, sGfxLockedBuffer* a_pData  );
	virtual skyVoid skyD3D11IndexBuffer::Unlock ( skyUInt a_uiSubresource );

// D3D11 Stuff
public:
	ID3D11Buffer* GetBaseBuffer() { return this->m_pBaseBuffer; }

private: 
	ID3D11Buffer* m_pBaseBuffer;

	skyD3D11IndexBuffer::skyD3D11IndexBuffer(  skyD3D11GfxDevice* a_pDevice, ID3D11Buffer* a_pBaseBuffer);
};