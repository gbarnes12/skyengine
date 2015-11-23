#pragma once

class skyGameObjectModule : public skyModule
{
	SKY_DECLARE_PROCESSIBLE(skyGameObjectModule, eProcessibleLevel_GameObject);
	SKY_DECLARE_MODULE(skyGameObjectModule, eModuleLevel_GameObject)
public:
	virtual skyResult skyGameObjectModule::Initialize();
	virtual skyResult skyGameObjectModule::Shutdown(); 
public:
	virtual skyVoid skyGameObjectModule::OnProcess();
};