#pragma once
//-----------------------------------------------------------------------------
// Include (Internal)
//-----------------------------------------------------------------------------
#include "inc_driver.h"

//-----------------------------------------------------------------------------
// Include (External)
//-----------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
#pragma warning(push)
#pragma warning(disable : 4005)
#include <d3d9.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <DxErr.h>
#include <D3DCompiler.h>
//#include "FWFontWrapper\FW1FontWrapper.h"
#pragma warning(pop)
#endif

//-----------------------------------------------------------------------------
// Libs (External)
//-----------------------------------------------------------------------------
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxguid.lib")
//#pragma comment ( lib, "FW1FontWrapper.lib" )

#if defined(SKY_BUILD_DEBUG)
#pragma comment (lib, "d3d9.lib")
#endif

//-----------------------------------------------------------------------------
// Libs (Internal)
//-----------------------------------------------------------------------------
#if defined(SKY_BUILD_DEBUG)
#pragma comment(lib, "Driver_D.lib")
#else
#pragma comment(lib, "Driver.lib")
#endif

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
class skyD3D11Resource;
class skyD3D11IndexBuffer;
class skyD3D11VertexBuffer;
class skyD3D11ConstantBuffer;
class skyD3D11DepthBuffer;
class skyD3D11StructuredBuffer;
class skyD3D11Texture;
class skyD3D11PixelShader;
class skyD3D11VertexShader;
class skyD3D11Font;
class skyD3D11Sprite;
class skyD3D11DepthStencilState;
class skyD3D11BlendState;
class skyD3D11SamplerState;
class skyD3D11RasterizerState;
class skyD3D11Primitive;
class skyD3D11RenderTarget;            
class skyD3D11ResourceManager;
class skyD3D11GfxStateManager;
class skyD3D11GfxSwapChain;
class skyD3D11GfxSystem;
class skyD3D11GfxDevice;
class skyD3D11Effect;
class skyGfxViewport;
class skyGfxFrustum;

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
#include "inc_drvd3d11_function.h"
#include "Systems\skyD3D11ResourceManager.h"
#include "Systems\skyD3D11GfxSwapChain.h"
#include "Systems\skyD3D11GfxSystem.h"
#include "Systems\skyD3D11GfxDevice.h"
#include "Systems\skyD3D11GfxStateManager.h"
#include "Resources\skyD3D11Resource.h"
#include "Resources\Buffers\skyD3D11IndexBuffer.h"
#include "Resources\Buffers\skyD3D11VertexBuffer.h" 
#include "Resources\Buffers\skyD3D11ConstantBuffer.h"
#include "Resources\Buffers\skyD3D11DepthBuffer.h"
#include "Resources\Textures\skyD3D11Texture.h"
#include "Resources\Textures\skyD3D11RenderTarget.h"
#include "Resources\Shaders\skyD3D11PixelShader.h"
#include "Resources\Shaders\skyD3D11VertexShader.h"
#include "Resources\Shaders\skyD3D11Effect.h"
#include "Resources\States\skyD3D11DepthStencilState.h"
#include "Resources\States\skyD3D11RasterizerState.h"
#include "Resources\States\skyD3D11SamplerState.h"
#include "Resources\Mesh\skyD3D11Primitive.h"
