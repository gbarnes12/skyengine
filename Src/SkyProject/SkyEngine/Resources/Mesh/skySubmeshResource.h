#pragma once
class skyIGfxPrimitive;
class skyMaterialResource;

class skySubmeshResource : public skyRefBaseClass
{
public:
	SKY_PROPERTY_GET(skyIGfxPrimitive*, m_pVisual, Visual);
	SKY_PROPERTY_GET(skyString, m_strName, Name);

	static skyResult skySubmeshResource::Spawn ( skyString a_strName, skySubmeshResource** a_pMesh );
	static skyResult skySubmeshResource::Spawn ( skyString a_strName, skyIGfxIndexBuffer* a_pIBuffer, skyIGfxVertexBuffer* a_pVBuffer, skySubmeshResource** a_pMesh );
	skySubmeshResource::~skySubmeshResource();
	// Set
public:
	skyVoid skySubmeshResource::SetVisual ( skyIGfxPrimitive* a_pVisual );
	skyVoid skySubmeshResource::SetMaterial ( skyMaterialResource* a_pMaterial );
	skyVoid skySubmeshResource::SetParent ( skyMeshResource* a_pParent );
public:
	skyVoid skySubmeshResource::Draw ( sGfxRenderObject* a_pObject );
	// Static
public:
	static skyVoid skySubmeshResource::RenderStatic (sGfxRenderObject* a_pObject);
private:
	skyMeshResource* m_pParent;
	skyIGfxPrimitive* m_pVisual;
	skyMaterialResource* m_pMaterial;
	skyString m_strName;

	skySubmeshResource::skySubmeshResource(skyIGfxPrimitive* a_pVisual, skyString a_strName);
};