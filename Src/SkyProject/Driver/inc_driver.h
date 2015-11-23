#pragma once

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
//#include <xnamath.h>
#include "inc_core.h"


#if defined(SKY_BUILD_DEBUG)
	#pragma comment (lib, "Core_D.lib")
#else
	#pragma comment (lib, "Core.lib")
#endif

//-----------------------------------------------------------------------------
// Forward Decelration (Graphic System)
//-----------------------------------------------------------------------------
class skyIGfxResource;
class skyIGfxIndexBuffer;
class skyIGfxVertexBuffer;
class skyIGfxConstantBuffer;
class skyIGfxDepthBuffer;
class skyIGfxStructuredBuffer;
class skyIGfxTexture;
class skyIGfxShader;
class skyIGfxEffect;
class skyIGfxFont;
class skyIGfxSprite;
class skyIGfxDepthStencilState;
class skyIGfxBlendState;
class skyIGfxSamplerState;
class skyIGfxRasterizerState;
class skyIGfxStateManager;
class skyIGfxPrimitive;
class skyIGfxRenderTarget;            
class skyIGfxResourceManager;
class skyIGfxSwapChain;
class skyIGfxSystem;
class skyIGfxDevice;
class skyGfxViewport;
class skyGfxFrustum;


//-----------------------------------------------------------------------------
// Forward Decelration (High Level Systems)
//-----------------------------------------------------------------------------
class skyIModule; 
class skyIProcessible;

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
#include "Graphics\inc_graphic_types.h"
#include "Graphics\inc_graphic_interfaces.h"
#include "Systems\inc_systems_interfaces.h"
