// stdafx.h : Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Teile der Windows-Header nicht einbinden.

#if defined(WIN32) 
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "User32.lib" )
#pragma comment ( lib, "Gdi32.lib" )
#endif


#include "inc_core.h"