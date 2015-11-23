#pragma once
#include "skyGfxRenderBatch.h"

class skyGfxRenderTechnique
{
public:
	typedef struct sGfxRenderTask 
	{
		std::vector<skyGfxRenderPass*> m_arrPasses;
		skyUInt m_uiPassCount;
	} sGfxRenderTask;

	skyGfxRenderTechnique();
	virtual skyVoid skyGfxRenderTechnique::Begin();
	virtual skyVoid skyGfxRenderTechnique::Execute(skyGfxRenderBatch* a_Batch);
	virtual skyVoid skyGfxRenderTechnique::End();
protected:
	sGfxRenderTask m_sTask;
};

class skyGfxDefaultTechnique : public skyGfxRenderTechnique
{
public:
	virtual skyVoid skyGfxDefaultTechnique::Begin();
};

class skyGfxDebugTechnique : public skyGfxRenderTechnique
{
public:
	virtual skyVoid skyGfxDebugTechnique::Begin();
	virtual skyVoid skyGfxDebugTechnique::End();
};