#include "stdafx.h"
#include "skyGfxRenderBatch.h"
#include "skyGfxRenderPass.h"


skyInt skyDoDebugObjectPass::Execute(skyGfxRenderBatch* a_Batch)
{
	// now process the objects and delete the objects afterwards!
	SKY_TODO("Make this more friendly since we always allocate dynamically each frame which is kind of meh...");
	
	DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Debug Draw");
	skyGfxDebugDrawManager::Instance().Prepare();
	a_Batch->ExecuteObjects(eGfxRenderSortId_Debug);
	skyGfxDebugDrawManager::Instance().ClearObjects();
	DX_END_SECTION();

	return 1;
}

skyInt skyRenderDynStaticPass::Execute(skyGfxRenderBatch* a_Batch)
{
	// now process the objects and delete the objects afterwards!
	SKY_TODO("Make this more friendly since we always allocate dynamically each frame which is kind of meh...");
	
	DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Dynamic and static objects");
	a_Batch->ExecuteObjects(eGfxRenderSortId_Static);
	DX_END_SECTION();

	return 1;
}


skyInt skyUpdatePerspectiveCamPass::Execute(skyGfxRenderBatch* a_Batch)
{
	DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Update perspective camera");
	skyCameraManager::Update();

	skyIGfxConstantBuffer* pConstantBuffer = skyGfxManager::ConstantMatrixBuffer();
	// Upload to constant buffer!
	if(pConstantBuffer)
	{
		sGfxLockedBuffer sLockedBuffer;
		SKY_ZERO_MEM(&sLockedBuffer, sizeof(sGfxLockedBuffer));
		pConstantBuffer->Lock(eGfxMapType_WriteDiscard, eGfxMapFlag_None, &sLockedBuffer);

		sMatrixBuffer* pBuffer = (sMatrixBuffer*)sLockedBuffer.m_pData;
		skyICamera* pCamera = skyCameraManager::GetCurrentCamera();
		if(pCamera)
		{
			pBuffer->m_sProjection = pCamera->GetProjection();
			pBuffer->m_sView = pCamera->GetView();
			pConstantBuffer->Unlock(sLockedBuffer.m_uiSubresource);
			skyGfxManager::SetConstantbuffer(eGfxShaderType_Vertex, 0, pConstantBuffer);
		}
	}

	DX_END_SECTION();
	return 1;
}