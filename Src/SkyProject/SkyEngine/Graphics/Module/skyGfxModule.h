#pragma once
#include "..\..\Rendersystem\skyGfxRenderTechnique.h"

class skyGfxModule : public skyModule
{
	SKY_DECLARE_PROCESSIBLE(skyGfxModule, eProcessibleLevel_Graphics);
	SKY_DECLARE_MODULE(skyGfxModule, eModuleLevel_Graphics)
public:
	virtual skyResult skyGfxModule::Initialize();
	virtual skyResult skyGfxModule::Shutdown(); 
public:
	virtual skyVoid skyGfxModule::OnProcess();
};