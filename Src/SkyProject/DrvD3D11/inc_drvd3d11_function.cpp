#include "stdafx.h"
#include "inc_drvd3d11_function.h"

skyResult skyCreateGfxSystem ( skyIGfxSystem** a_pSystem )
{
	skyIGfxSystem* pSystem = nullptr;

	skyResult hr = skyD3D11GfxSystem::Spawn(&pSystem);
	if(hr != SKY_OK)
		return SKY_INVALID_POINTER;

	*a_pSystem = pSystem;

	return SKY_OK;
}

skyVoid skyPerfEventStart ( const skyColor& a_sColor, const std::wstring& a_strName )
{
	#if defined(SKY_BUILD_DEBUG)
	D3DPERF_BeginEvent(D3DXCOLOR(a_sColor.R(), a_sColor.G(), a_sColor.B(), a_sColor.A()), a_strName.c_str());
	#endif
}

skyVoid skyPerfEventEnd ( )
{
	#if defined(SKY_BUILD_DEBUG)
	D3DPERF_EndEvent();
	#endif
}