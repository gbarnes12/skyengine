#pragma once

class skyD3D11Primitive 
	: public skyIGfxPrimitive, public skyD3D11Resource
{
public:
	static skyResult skyD3D11Primitive::Spawn (  skyD3D11GfxDevice* a_pDevice, skyD3D11Primitive** a_pPrimitive );

	virtual skyD3D11Primitive::~skyD3D11Primitive();
public:
	eGfxResourceType skyD3D11Primitive::GetType ( skyVoid ) { return eGfxResourceType_Primitive; }
public:
	virtual skyVoid skyD3D11Primitive::SetFillMode ( eGfxFillMode a_eMode );
	virtual skyVoid skyD3D11Primitive::EnableZWrite ( skyVoid );
public:
	virtual skyVoid skyD3D11Primitive::SetIndices ( skyIGfxIndexBuffer* a_pVertices );
	virtual skyIGfxIndexBuffer* skyD3D11Primitive::GetIndices ( skyVoid ) const;
public:
	virtual skyVoid skyD3D11Primitive::SetVertices ( skyIGfxVertexBuffer* a_pVertices );
	virtual skyIGfxVertexBuffer* skyD3D11Primitive::GetVertices ( skyVoid ) const;

private:
	skyD3D11IndexBuffer* m_pIndexBuffer;
	skyD3D11VertexBuffer* m_pVertexBuffer;

	skyD3D11Primitive::skyD3D11Primitive(  skyD3D11GfxDevice* a_pDevice );

};