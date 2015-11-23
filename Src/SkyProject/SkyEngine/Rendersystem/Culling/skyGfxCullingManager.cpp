#include "stdafx.h"
#include "skyGfxCullingManager.h"


skyResult skyGfxCullingManager::Initialize()
{
	return SKY_OK;
}

skyResult skyGfxCullingManager::Shutdown()
{
	this->m_arrObjects.clear();
	return SKY_OK;
}

skyVoid skyGfxCullingManager::AddObject( sGfxRenderObject* a_pObject )
{
	this->m_arrObjects.push_back(a_pObject);
}

skyVoid skyGfxCullingManager::ExtractObjects( skyGfxRenderBatch& a_Batch )
{
	for(skyUInt i = 0; i < m_arrObjects.size(); i++)
		a_Batch.AddObject(m_arrObjects[i]);
}

skyVoid skyGfxCullingManager::ClearObjects ()
{
	for(skyUInt i = 0; i < m_arrObjects.size(); i++)
	{
		SKY_SAFE_DELETE(m_arrObjects[i]);
	}

	m_arrObjects.clear();
}