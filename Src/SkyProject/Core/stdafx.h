// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Teile der Windows-Header nicht einbinden.

#if defined(WIN32) 
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "User32.lib" )
#pragma comment ( lib, "Gdi32.lib" )
#endif


#include "inc_core.h"