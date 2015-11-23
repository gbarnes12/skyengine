#pragma once
#include "skyGfxRenderBatch.h"

class skyGfxRenderPass
{
public:
	virtual ~skyGfxRenderPass() {}

	virtual skyInt skyGfxRenderPass::Begin ( ) { return 1; }
	virtual skyInt skyGfxRenderPass::Execute ( skyGfxRenderBatch* a_Batch ) { return 1; }
	virtual skyInt skyGfxRenderPass::End( ) { return 1; }
};


class skyRenderDynStaticPass : public skyGfxRenderPass 
{
public:
	skyRenderDynStaticPass() {}

	skyInt skyRenderDynStaticPass::Execute(skyGfxRenderBatch* a_Batch);
};

class skyClearRenderTargetPass : public skyGfxRenderPass
{
public:
	skyClearRenderTargetPass(skyUInt a_u32Slot, sGfxColor a_sColor)
		: m_u32Slot(a_u32Slot)
		, m_sColor(a_sColor)
	{

	}

	skyInt skyClearRenderTargetPass::Execute(skyGfxRenderBatch* a_Batch)
	{
		skyGfxManager::ClearRenderTarget(m_u32Slot, m_sColor);
		return 1;
	}

private:
	sGfxColor m_sColor;
	skyUInt m_u32Slot;
};

class skySetRenderTargetPass : public skyGfxRenderPass
{
public:
	skySetRenderTargetPass(skyUInt a_u32Slot, skyIGfxRenderTarget* a_pRenderTarget)
		: m_u32Slot(a_u32Slot)
		, m_pRenderTarget(a_pRenderTarget)
	{

	}

	skyInt skySetRenderTargetPass::Execute(skyGfxRenderBatch* a_Batch)
	{
		skyGfxManager::SetRenderTarget(m_u32Slot, m_pRenderTarget, false);
		return 1;
	}
private:
	skyUInt m_u32Slot;
	skyIGfxRenderTarget* m_pRenderTarget;
};

class skyDoDebugObjectPass : public skyGfxRenderPass
{
public:
	skyDoDebugObjectPass() {}

	skyInt skyDoDebugObjectPass::Execute(skyGfxRenderBatch* a_Batch);
};

class skyUpdatePerspectiveCamPass : public skyGfxRenderPass
{
public:
	skyUpdatePerspectiveCamPass() {
	}
	skyInt skyUpdatePerspectiveCamPass::Execute(skyGfxRenderBatch* a_Batch);
};