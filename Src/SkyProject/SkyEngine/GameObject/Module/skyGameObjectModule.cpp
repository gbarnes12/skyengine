#include "stdafx.h"
#include "skyGameObjectModule.h"

SKY_DEFINE_PROCESSIBLE(skyGameObjectModule);
SKY_DEFINE_MODULE(skyGameObjectModule)

skyResult skyGameObjectModule::Initialize()
{
	skyResult hr;
	m_cProcess.Register(this);

	SKY_VR(skyGameObjectManager::Initialize());

	return SKY_OK;
}

skyResult skyGameObjectModule::Shutdown()
{
	skyResult hr;
	m_cProcess.Unregister();

	SKY_VR(skyGameObjectManager::Shutdown());

	return SKY_OK;
}

skyVoid skyGameObjectModule::OnProcess()
{
	skyGameObjectManager::Update(0.0f);
}