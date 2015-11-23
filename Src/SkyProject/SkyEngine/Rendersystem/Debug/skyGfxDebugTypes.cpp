#include "stdafx.h"
#include "..\skyGfxRenderBatch.h"
#include "skyGfxDebugTypes.h"


skyVoid skyGfxDebugLineObject::skyDebugCallDrawMethod(sGfxRenderObject* a_pObject)
{
	skyGfxDebugObject* pObject = static_cast<skyGfxDebugObject*>(a_pObject->m_pInstance);
	if(pObject)
		pObject->Draw(a_pObject);
}


skyResult skyGfxDebugLineObject::Spawn (sGfxVector4& a_sBegin, sGfxVector4& a_sEnd, sGfxColor& a_sColor
										, skyIGfxShader* a_pShader, skyGfxDebugLineObject** a_pLine )
{
	if(!a_pShader)
		return SKY_INVALID_POINTER;

	skyResult hr;
	skyIGfxVertexBuffer* pVBuffer = nullptr;

	sGfxVertexDesc VertexDesc;
	SKY_ZERO_MEM(&VertexDesc, sizeof(sGfxVertexDesc));
	VertexDesc.m_uiCount = 2;
	VertexDesc.m_uiSize = sizeof(sGfxDebugVertex);
	VertexDesc.m_eUsage = eGfxUsage_Dynamic;
	VertexDesc.m_eCPUAccess = eGfxCpuAccessFlags_Write;
	
	sGfxDrawDesc DrawDesc;
	SKY_ZERO_MEM(&DrawDesc, sizeof(sGfxDrawDesc));
	DrawDesc.m_bInstanced = SKY_FALSE;
	DrawDesc.m_ePrimitiveType = eGfxPrimitiveType_LineList;
	DrawDesc.m_uiIndexCount = 0;
	DrawDesc.m_uiInstanceCount = 0;
	DrawDesc.m_uiVertexCount = 2;
	DrawDesc.m_uiVertexLocation = 0;
	sGfxDebugVertex arrVertices[] = {
		{skyVector3(0.5f, 0.5f, 0.0f), skyColor(1.0f, 0.0f, 0.0f, 1.0f)},
		{skyVector3(1.0f, 1.0f, 0.0f), skyColor(1.0f, 0.0f, 0.0f, 1.0f)}
	};


	SKY_VR(skyGfxManager::CreateVertexBuffer(&pVBuffer, VertexDesc));
	
	sGfxLockedBuffer LockedBuffer;
	SKY_ZERO_MEM(&LockedBuffer, sizeof(sGfxLockedBuffer));

	SKY_VR(pVBuffer->Lock(eGfxMapType_WriteDiscard, eGfxMapFlag_DoNotWait, &LockedBuffer));
	memcpy(LockedBuffer.m_pData, arrVertices, sizeof(sGfxDebugVertex) * 2); 
	pVBuffer->Unlock(LockedBuffer.m_uiSubresource);
	pVBuffer->SetStride(sizeof(sGfxDebugVertex));

	skyGfxDebugLineObject* pLine = SKY_NEW skyGfxDebugLineObject(a_pShader, pVBuffer, DrawDesc);
	if(!pLine)
		return SKY_OUT_OF_MEMORY;

	// submit the renderobject!
	SKY_SUBMIT_RENDEROBJ((skyUInt)eGfxRenderSortId_Debug, (skyUInt)0, &skyGfxDebugLineObject::skyDebugCallDrawMethod, (skyVoid*)pLine);

	*a_pLine = pLine;

	return SKY_OK;
}

skyVoid skyGfxDebugLineObject::Draw ( sGfxRenderObject* a_pObject )
{
	skyGfxManager::SetVertexBuffer(m_pVertexBuffer, 0);
	skyGfxManager::Draw(m_sDrawDesc);
}



skyResult skyGfxDebugTriangleObject::Spawn (sGfxVector4& a_sPosition, sGfxColor& a_sColor
										, skyIGfxShader* a_pShader, skyGfxDebugTriangleObject** a_pTriangle )
{
	if(!a_pShader)
		return SKY_INVALID_POINTER;

	skyResult hr;
	skyIGfxVertexBuffer* pVBuffer = nullptr;

	sGfxVertexDesc VertexDesc;
	SKY_ZERO_MEM(&VertexDesc, sizeof(sGfxVertexDesc));
	VertexDesc.m_uiCount = 3;
	VertexDesc.m_uiSize = sizeof(sGfxDebugVertex);
	VertexDesc.m_eUsage = eGfxUsage_Dynamic;
	VertexDesc.m_eCPUAccess = eGfxCpuAccessFlags_Write;
	
	sGfxDrawDesc DrawDesc;
	SKY_ZERO_MEM(&DrawDesc, sizeof(sGfxDrawDesc));
	DrawDesc.m_bInstanced = SKY_FALSE;
	DrawDesc.m_ePrimitiveType = eGfxPrimitiveType_TriangleList;
	DrawDesc.m_uiIndexCount = 0;
	DrawDesc.m_uiInstanceCount = 0;
	DrawDesc.m_uiVertexCount = 3;
	DrawDesc.m_uiVertexLocation = 0;

	sGfxDebugVertex arrVertices[] = {
		{skyVector3(0.0f, 0.5f, 0.0f), skyColor(1.0f, 0.0f, 0.0f, 1.0f).ToVector4()},
		{skyVector3(0.45f, -0.5, 0.0f), skyColor(1.0f, 0.0f, 0.0f, 1.0f).ToVector4()},
		{skyVector3(-0.45f, -0.5f, 0.0f), skyColor(1.0f, 0.0f, 0.0f, 1.0f).ToVector4()}
	};

	SKY_VR(skyGfxManager::CreateVertexBuffer(&pVBuffer, VertexDesc));
	
	sGfxLockedBuffer LockedBuffer;
	SKY_ZERO_MEM(&LockedBuffer, sizeof(sGfxLockedBuffer));

	SKY_VR(pVBuffer->Lock(eGfxMapType_WriteDiscard, eGfxMapFlag_DoNotWait, &LockedBuffer));
	memcpy(LockedBuffer.m_pData, arrVertices, sizeof(sGfxDebugVertex) * 3); 
	pVBuffer->Unlock(LockedBuffer.m_uiSubresource);
	pVBuffer->SetStride(sizeof(sGfxDebugVertex));

	skyGfxDebugTriangleObject* pTriangle = SKY_NEW skyGfxDebugTriangleObject(a_pShader, pVBuffer, DrawDesc);
	if(!pTriangle)
		return SKY_OUT_OF_MEMORY;

	// submit the renderobject!
	SKY_SUBMIT_RENDEROBJ((skyUInt)eGfxRenderSortId_Debug, (skyUInt)0, &skyGfxDebugTriangleObject::skyDebugCallDrawMethod, (skyVoid*)pTriangle);

	*a_pTriangle = pTriangle;



	return SKY_OK;
}

skyVoid skyGfxDebugTriangleObject::skyDebugCallDrawMethod(sGfxRenderObject* a_pObject)
{
	skyGfxDebugObject* pObject = static_cast<skyGfxDebugObject*>(a_pObject->m_pInstance);
	if(pObject)
		pObject->Draw(a_pObject);
}

skyVoid skyGfxDebugTriangleObject::Draw ( sGfxRenderObject* a_pObject )
{
	skyGfxManager::SetVertexBuffer(m_pVertexBuffer, 0);
	skyGfxManager::Draw(m_sDrawDesc);
}