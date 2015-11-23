#pragma once 

class skyD3D11GfxSystem 
	: public skyIGfxSystem
{
public:
	static skyResult skyD3D11GfxSystem::Spawn ( skyIGfxSystem** a_pSystem );
	skyD3D11GfxSystem::~skyD3D11GfxSystem();

public:
	virtual skyResult skyD3D11GfxSystem::CreateDevice ( sGfxDeviceDesc& a_sDesc, skyIGfxDevice** a_pDevice );

private:
	skyD3D11GfxDevice* m_pDevice;

	skyD3D11GfxSystem::skyD3D11GfxSystem();
};