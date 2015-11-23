#pragma once

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
#include "inc_engine.h"


//-----------------------------------------------------------------------------
// Libs
//-----------------------------------------------------------------------------
#if defined(SKY_BUILD_DEBUG)
#pragma comment(lib, "Engine_D.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif


//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
class GameApplication;


//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
#include "Application\GameApplication.h"


