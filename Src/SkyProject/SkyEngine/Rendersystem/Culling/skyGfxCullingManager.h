#pragma once

class skyGfxCullingManager : public skySingleton<skyGfxCullingManager>
{
public:
	skyResult skyGfxCullingManager::Initialize();
	skyResult skyGfxCullingManager::Shutdown();

	skyVoid skyGfxCullingManager::AddObject( sGfxRenderObject* a_pObject );
	skyVoid skyGfxCullingManager::ExtractObjects( skyGfxRenderBatch& a_Batch );
	skyVoid skyGfxCullingManager::ClearObjects ();
private:
	std::vector<sGfxRenderObject*> m_arrObjects;
};