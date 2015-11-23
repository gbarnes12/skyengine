#include "stdafx.h"
#include "skyD3D11GfxSystem.h"


skyResult skyD3D11GfxSystem::Spawn ( skyIGfxSystem** a_pSystem )
{
	*a_pSystem = SKY_NEW skyD3D11GfxSystem();
	return SKY_OK;
}


skyD3D11GfxSystem::skyD3D11GfxSystem() :
	m_pDevice (nullptr)
{
}

skyD3D11GfxSystem::~skyD3D11GfxSystem()
{
	SKY_SAFE_DELETE(m_pDevice);
}


skyResult skyD3D11GfxSystem::CreateDevice ( sGfxDeviceDesc& a_sDesc, skyIGfxDevice** a_pDevice )
{
	skyD3D11GfxDevice* l_pDevice = nullptr;

	if(m_pDevice)
		*a_pDevice = m_pDevice;

	
	skyResult hr = skyD3D11GfxDevice::Spawn(a_sDesc, &l_pDevice);
	if(hr != SKY_OK)
		return SKY_INVALID_POINTER;

	m_pDevice = l_pDevice;
	*a_pDevice = m_pDevice;

	return SKY_OK;
}
