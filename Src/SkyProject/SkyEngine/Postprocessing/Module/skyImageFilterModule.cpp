#include "stdafx.h"
#include "skyImageFilterModule.h"


SKY_DEFINE_PROCESSIBLE(skyImageFilterModule);
SKY_DEFINE_MODULE(skyImageFilterModule)


skyResult skyImageFilterModule::Initialize()
{
	skyResult hr;
	m_cProcess.Register(this);
	SKY_VR(skyImageFilterManager::Initialize());
	return SKY_OK;
}

skyResult skyImageFilterModule::Shutdown()
{
	skyResult hr;
	m_cProcess.Unregister();
	SKY_VR(skyImageFilterManager::Shutdown());
	return SKY_OK;
}

skyVoid skyImageFilterModule::OnProcess()
{
	skyImageFilterManager::Update();
}