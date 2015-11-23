#include "stdafx.h"
#include "..\System\skyGfxManager.h"
#include "..\..\Rendersystem\skyGfxRenderTechnique.h"
#include "skyGfxModule.h"

sGfxPresentDesc g_sPresentDesc;

SKY_DEFINE_PROCESSIBLE(skyGfxModule);
SKY_DEFINE_MODULE(skyGfxModule)

skyResult skyGfxModule::Initialize()
{
	skyResult hr;
	m_cProcess.Register(this);

	SKY_ZERO_MEM(&g_sPresentDesc, sizeof(sGfxPresentDesc));
	g_sPresentDesc.m_uiSyncInterval = 0;

	SKY_VR(skyGfxManager::Initialize());
	SKY_VR(skyGfxDebugDrawManager::Instance().Initialize());

	return SKY_OK;
}

skyResult skyGfxModule::Shutdown()
{
	skyResult hr;

	m_cProcess.Unregister();
	SKY_VR(skyGfxDebugDrawManager::Instance().Shutdown());
	SKY_VR(skyGfxManager::Shutdown());

	return SKY_OK;
}

skyVoid skyGfxModule::OnProcess()
{
	skyGfxManager::Present(g_sPresentDesc);
}