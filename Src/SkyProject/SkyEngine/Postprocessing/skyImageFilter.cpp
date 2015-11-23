#include "stdafx.h"
#include "skyImageFilter.h"


skyVoid skySceneImageFilter::Update(skyGfxRenderBatch* a_Batch)
{
	m_Technique.Begin();
	m_Technique.Execute(a_Batch);
	m_Technique.End();
}

 skyVoid skyDebugImageFilter::Update(skyGfxRenderBatch* a_Batch)
 {
	m_Technique.Begin();
	m_Technique.Execute(a_Batch);
	m_Technique.End();
 }