#include "stdafx.h"
#include "skySubmeshResource.h"

skyResult skySubmeshResource::Spawn ( skyString a_strName, skySubmeshResource** a_pMesh )
{
	skyResult hr;
	skySubmeshResource* pMesh = nullptr;
	skyIGfxPrimitive* pVisual = nullptr;

	SKY_VR(skyGfxManager::CreatePrimitive(&pVisual));

	pMesh = SKY_NEW skySubmeshResource(pVisual, a_strName);

	*a_pMesh = pMesh;

	return SKY_OK;
}

skyResult skySubmeshResource::Spawn ( skyString a_strName, skyIGfxIndexBuffer* a_pIBuffer, skyIGfxVertexBuffer* a_pVBuffer, skySubmeshResource** a_pMesh )
{
	skyResult hr;
	skySubmeshResource* pMesh = nullptr;
	skyIGfxPrimitive* pVisual = nullptr;

	SKY_VR(skyGfxManager::CreatePrimitive(&pVisual));
	pVisual->SetIndices(a_pIBuffer);
	pVisual->SetVertices(a_pVBuffer);

	pMesh = SKY_NEW skySubmeshResource(pVisual, a_strName);
	
	*a_pMesh = pMesh;

	return SKY_OK;
}

skySubmeshResource::skySubmeshResource(skyIGfxPrimitive* a_pVisual, skyString a_strName)
	: m_pVisual(a_pVisual)
	, m_strName(a_strName)
	, m_pMaterial(nullptr)
{
}

skySubmeshResource::~skySubmeshResource()
{
	SKY_RELEASE(m_pMaterial);
	SKY_SAFE_DELETE(m_pVisual);
}

skyVoid skySubmeshResource::SetVisual ( skyIGfxPrimitive* a_pVisual )
{
	SKY_SAFE_DELETE(m_pVisual);

	this->m_pVisual = a_pVisual;
}

skyVoid skySubmeshResource::SetParent ( skyMeshResource* a_pParent )
{
	this->m_pParent = a_pParent;
}

skyVoid skySubmeshResource::SetMaterial ( skyMaterialResource* a_pMaterial )
{
	SKY_RELEASE(m_pMaterial);

	m_pMaterial = a_pMaterial;
	if(m_pMaterial)
		m_pMaterial->AddRef();
}

skyVoid skySubmeshResource::RenderStatic (sGfxRenderObject* a_pObject)
{
	skySubmeshResource* pObject = static_cast<skySubmeshResource*>(a_pObject->m_pInstance);
	if(pObject)
		pObject->Draw(a_pObject);
}

skyVoid skySubmeshResource::Draw ( sGfxRenderObject* a_pObject )
{
	skyWString wName(this->m_strName.begin(), this->m_strName.end());
	DX_START_SECTION(skyColor(1.0f, 1.0f, 0.0f, 1.0f), L"Submesh[Name:" + wName + L"]");

	if(m_pMaterial)
		m_pMaterial->Apply(this->m_pParent->m_pEffect);
	this->m_pParent->m_pEffect->Execute();
	skyGfxManager::Draw(this->m_pVisual);

	DX_END_SECTION();
}