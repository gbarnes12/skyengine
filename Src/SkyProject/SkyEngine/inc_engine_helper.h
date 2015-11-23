#pragma once

#define SKY_VR_GFX() if(!g_GfxDevice) { return SKY_INVALID_POINTER; }
#define SKY_V_GFX() if(!g_GfxDevice) { return; }