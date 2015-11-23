#include "stdafx.h"
#include "skyGfxRenderPass.h"
#include "skyGfxRenderTechnique.h"

const skyUInt g_uiMaxPasses = 128;


skyGfxRenderTechnique::skyGfxRenderTechnique()
{
	SKY_ZERO_MEM(&m_sTask, sizeof(sGfxRenderTask));
}

skyVoid skyGfxRenderTechnique::Begin()
{
#define _ADD_PASS(_TYPE_) assert(g_uiMaxPasses > m_sTask.m_uiPassCount); m_sTask.m_arrPasses.push_back(SKY_NEW _TYPE_); m_sTask.m_uiPassCount++;
	
	
	for(skyUInt i = 0; i < m_sTask.m_uiPassCount;)
		i += m_sTask.m_arrPasses[i]->Begin();
}

skyVoid skyGfxRenderTechnique::Execute(skyGfxRenderBatch* a_Batch)
{
	for(skyUInt i = 0; i < m_sTask.m_uiPassCount;)
		i += m_sTask.m_arrPasses[i]->Execute(a_Batch);
}

skyVoid skyGfxRenderTechnique::End()
{
	for(skyUInt i = 0; i < m_sTask.m_uiPassCount;) {
		skyUInt y = m_sTask.m_arrPasses[i]->End();

		if(y != 0)
			SKY_SAFE_DELETE(m_sTask.m_arrPasses[i]);  

		i+= y;
	}
	
	m_sTask.m_arrPasses.clear();
}


skyVoid skyGfxDefaultTechnique::Begin() 
{ 
	m_sTask.m_uiPassCount = 0;
	
	// final rendering!
	_ADD_PASS(skySetRenderTargetPass(0, skyGfxManager::BackBufferRT()));
	_ADD_PASS(skyClearRenderTargetPass(0, skyColor(0.0f, 0.2f, 0.4f, 1.0f)));
	_ADD_PASS(skyUpdatePerspectiveCamPass());
	_ADD_PASS(skyRenderDynStaticPass());

	__super::Begin();
}


skyVoid skyGfxDebugTechnique::Begin() 
{ 
	m_sTask.m_arrPasses.clear();
	m_sTask.m_uiPassCount = 0;
	
	// Do the deug object pass ;)
	_ADD_PASS(skyDoDebugObjectPass());


	__super::Begin();
}

skyVoid skyGfxDebugTechnique::End()
{
	__super::End();
}
