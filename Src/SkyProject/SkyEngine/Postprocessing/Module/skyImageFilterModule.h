#pragma once


class skyImageFilterModule  : public skyModule
{
	SKY_DECLARE_PROCESSIBLE(skyImageFilterModule, eProcessibleLevel_Postprocess);
	SKY_DECLARE_MODULE(skyImageFilterModule, eModuleLevel_Postprocess)
public:
	virtual skyResult skyImageFilterModule::Initialize();
	virtual skyResult skyImageFilterModule::Shutdown(); 
public:
	virtual skyVoid skyImageFilterModule::OnProcess();
};
