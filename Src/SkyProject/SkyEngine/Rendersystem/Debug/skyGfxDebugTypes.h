#pragma once

class skyGfxRenderObject;

class skyGfxDebugObject
{
public:
	virtual ~skyGfxDebugObject()
	{
		SKY_SAFE_DELETE(m_pVertexBuffer);
	}

	virtual skyVoid skyGfxDebugObject::Draw ( sGfxRenderObject* a_pObject ) = 0;

protected:
	skyIGfxShader* m_pShader;
	skyIGfxVertexBuffer* m_pVertexBuffer;
	sGfxDrawDesc m_sDrawDesc;

	skyGfxDebugObject(skyIGfxShader* a_pShader, skyIGfxVertexBuffer* a_pVertexBuffer, sGfxDrawDesc a_sDrawDesc)
		: m_pShader(a_pShader)
		, m_pVertexBuffer(a_pVertexBuffer)
		, m_sDrawDesc(a_sDrawDesc)
	{
	}
};

// SKY_SUBMIT_RENDEROBJ(eGfxRenderSortId_Debug, 0, &skyGfxDebugLineObject::Draw);

class skyGfxDebugLineObject : public skyGfxDebugObject
{
public:
	virtual skyGfxDebugLineObject::~skyGfxDebugLineObject()
	{
	}

	static skyResult skyGfxDebugLineObject::Spawn ( sGfxVector4& a_sBegin, sGfxVector4& a_sEnd, sGfxColor& a_sColor, 
			skyIGfxShader* a_pShader, skyGfxDebugLineObject** a_pLine );

	static skyVoid skyGfxDebugLineObject::skyDebugCallDrawMethod(sGfxRenderObject* a_pObject);
	virtual skyVoid skyGfxDebugLineObject::Draw ( sGfxRenderObject* a_pObject );
private:
	skyGfxDebugLineObject(skyIGfxShader* a_pShader, skyIGfxVertexBuffer* a_pVertexBuffer, sGfxDrawDesc a_sDrawDesc)
		: skyGfxDebugObject(a_pShader, a_pVertexBuffer, a_sDrawDesc)
	{
	}
};


class skyGfxDebugTriangleObject : public skyGfxDebugObject
{
public:
	virtual skyGfxDebugTriangleObject::~skyGfxDebugTriangleObject()
	{
	}

	static skyResult skyGfxDebugTriangleObject::Spawn ( sGfxVector4& a_sPosition, sGfxColor& a_sColor, 
			skyIGfxShader* a_pShader, skyGfxDebugTriangleObject** a_pTriangle );

	static skyVoid skyGfxDebugTriangleObject::skyDebugCallDrawMethod(sGfxRenderObject* a_pObject);
	virtual skyVoid skyGfxDebugTriangleObject::Draw ( sGfxRenderObject* a_pObject );
private:
	skyGfxDebugTriangleObject(skyIGfxShader* a_pShader, skyIGfxVertexBuffer* a_pVertexBuffer, sGfxDrawDesc a_sDrawDesc)
		: skyGfxDebugObject(a_pShader, a_pVertexBuffer, a_sDrawDesc)
	{
	}
};

