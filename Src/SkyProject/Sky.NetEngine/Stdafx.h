// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#include "SkyEngine.h"


#if !defined(SKY_BUILD_RELEASE)
#pragma comment(lib, "SkyEngine_D.lib")

#else if
#pragma comment(lib, "SkyEngine.lib")

#endif

