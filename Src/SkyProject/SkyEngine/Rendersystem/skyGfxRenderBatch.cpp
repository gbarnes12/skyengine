#include "stdafx.h"
#include "skyGfxRenderbatch.h"

skyBool skyCompareRenderObject (const void * a, const void * b)
{
	return (*(sGfxRenderObject*)a).m_u32MaterialId < (*(sGfxRenderObject*)b).m_u32MaterialId;
}

skyVoid skyGfxRenderBatch::AddObject ( sGfxRenderObject* a_pObject )
{
	if(a_pObject->m_pCallback)
	{
		skyInt index = (skyInt)a_pObject->m_u32SortId;
		
		this->m_arrRenderContexts[index].m_arrRenderObjects.push_back(a_pObject);
	}
}

skyVoid skyGfxRenderBatch::ExecuteObjects ( skyUInt a_u32SortId )
{
	// sort items with material id
	skyInt index = (skyInt)a_u32SortId;
	std::vector<sGfxRenderObject*>& RenderObjs = this->m_arrRenderContexts[index].m_arrRenderObjects;
	if(RenderObjs.size() == 0)
		return;
	SKY_TODO("Sort of render objects doesn't work somehow?");
	//if(RenderObjs.size() > 1)
	//	std::sort(RenderObjs.begin(), RenderObjs.end(), skyCompareRenderObject);

	// call the callbacks 
	for(skyUInt i = 0; i < RenderObjs.size(); i++)
	{
		sGfxRenderObject* pObject = RenderObjs[i];
		pObject->m_pCallback(pObject);
	}

	// just clear the list of objects!
	RenderObjs.clear();
}

skyVoid skyGfxRenderBatch::ClearObjects ()
{
	for(skyUInt i = 0; i < eGfxRenderSortId_Count; i++)
	{
		std::vector<sGfxRenderObject*>& RenderObjs = this->m_arrRenderContexts[i].m_arrRenderObjects;
		RenderObjs.clear();
	}
}
