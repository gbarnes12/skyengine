#pragma once

typedef skyVoid (*skyGfxRenderObjectCallback)(sGfxRenderObject* a_pObject);
typedef std::vector<sGfxRenderObject*> skyRenderObjectArray;

struct sGfxRenderObject
{
	skyUInt m_u32SortId;
	skyUInt m_u32MaterialId;
	skyGfxRenderObjectCallback m_pCallback;
	skyVoid* m_pInstance;
	sGfxBoundingSphere* m_pSphere;

	sGfxRenderObject(skyUInt a_u32SortId, skyUInt a_u32MaterialId
		, skyGfxRenderObjectCallback a_pCallback, skyVoid* a_pInstance)
		: m_u32SortId(a_u32SortId)
		, m_u32MaterialId(a_u32MaterialId)
		, m_pCallback (a_pCallback)
		, m_pInstance (a_pInstance)
		, m_pSphere (nullptr)
	{
	}
};

struct sGfxRenderContext
{
	skyRenderObjectArray m_arrRenderObjects;
};



class skyGfxRenderBatch
{
public:
	skyVoid skyGfxRenderBatch::AddObject ( sGfxRenderObject* a_pObject );
	skyVoid skyGfxRenderBatch::ExecuteObjects ( skyUInt a_u32SortId );
	skyVoid skyGfxRenderBatch::ClearObjects ();

private:
	sGfxRenderContext m_arrRenderContexts[eGfxRenderSortId_Count];
};


#define SKY_SUBMIT_RENDEROBJ(_SORTID_, _MATID_, _CALLBACK_, _INSTANCE_) \
	sGfxRenderObject* pRenderObject = nullptr; \
	if(_CALLBACK_ != NULL) { \
		pRenderObject = SKY_NEW sGfxRenderObject(_SORTID_, _MATID_, _CALLBACK_, _INSTANCE_);\
		skyGfxCullingManager::Instance().AddObject(pRenderObject); \
	}
