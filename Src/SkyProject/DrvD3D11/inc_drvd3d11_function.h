#pragma once

extern skyVoid skyPerfEventStart ( const skyColor& a_sColor, const std::wstring& a_strName );
extern skyVoid skyPerfEventEnd ( );
extern skyResult skyCreateGfxSystem ( skyIGfxSystem** a_pSystem );


//-----------------------------------------------------------------------------
// PIX 
//-----------------------------------------------------------------------------
#define DX_START_SECTION(_COLOR_,_NAME_) skyPerfEventStart(_COLOR_,_NAME_);
#define DX_END_SECTION() skyPerfEventEnd();