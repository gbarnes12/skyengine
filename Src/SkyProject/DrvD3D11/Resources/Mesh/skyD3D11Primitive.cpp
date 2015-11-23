#include "stdafx.h"
#include "skyD3D11Primitive.h"

skyResult skyD3D11Primitive::Spawn (  skyD3D11GfxDevice* a_pDevice, skyD3D11Primitive** a_pPrimitive )
{
	if ( !a_pDevice )
	{
		SKY_PRINT_CONSOLE("error", "error while spawning new primitive. You have passed an invalid pointer.", 0x01);
		return SKY_INVALID_POINTER;
	}
	
	skyD3D11Primitive* pPrimitive = nullptr;

	pPrimitive = SKY_NEW skyD3D11Primitive(a_pDevice);
	if(!pPrimitive)
		return SKY_OUT_OF_MEMORY;

	*a_pPrimitive = pPrimitive;

	return SKY_OK;

}

skyD3D11Primitive::skyD3D11Primitive(  skyD3D11GfxDevice* a_pDevice )
	: skyD3D11Resource(a_pDevice)
	, m_pIndexBuffer(NULL)
	, m_pVertexBuffer(NULL)
{
}

skyD3D11Primitive::~skyD3D11Primitive()
{
	SKY_SAFE_DELETE(this->m_pIndexBuffer);
	SKY_SAFE_DELETE(this->m_pVertexBuffer);
}

skyVoid skyD3D11Primitive::SetFillMode ( eGfxFillMode a_eMode )
{
}

skyVoid skyD3D11Primitive::EnableZWrite ( skyVoid )
{
}

skyVoid skyD3D11Primitive::SetIndices ( skyIGfxIndexBuffer* a_pVertices )
{
	SKY_SAFE_DELETE(this->m_pIndexBuffer);
	this->m_pIndexBuffer = static_cast<skyD3D11IndexBuffer*>(a_pVertices);
}

skyIGfxIndexBuffer* skyD3D11Primitive::GetIndices ( skyVoid ) const
{
	return this->m_pIndexBuffer;
}

skyVoid skyD3D11Primitive::SetVertices ( skyIGfxVertexBuffer* a_pVertices )
{
	SKY_SAFE_DELETE(this->m_pVertexBuffer);
	this->m_pVertexBuffer = static_cast<skyD3D11VertexBuffer*>(a_pVertices);
}

skyIGfxVertexBuffer* skyD3D11Primitive::GetVertices ( skyVoid ) const
{
	return this->m_pVertexBuffer;
}
