#pragma once

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
//#include "inc_core.h"
#include "inc_driver.h"
#include "inc_drvd3d11.h"
#include "inc_resource.h"
#include "Extern\rapidjson\document.h"

//-----------------------------------------------------------------------------
// External Include
//-----------------------------------------------------------------------------
#include "tinyxml_2_6_2\tinyxml.h"

/* old stuff in case someone still want glm 
include it again!
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>
*/

#pragma warning(push)
#pragma warning(disable : 4221)
#include "angelscript\angelscript.h"
#pragma warning(pop)


//-----------------------------------------------------------------------------
// Internal Libs
//-----------------------------------------------------------------------------
#define SKY_USE_D3D11

#if defined(SKY_BUILD_DEBUG)
#pragma comment ( lib, "Driver_D.lib" )
#pragma comment ( lib, "Resource_D.lib" )
#if defined(SKY_USE_D3D11)
#pragma comment ( lib, "DrvD3D11_D.lib" )
#endif

#else
#pragma comment ( lib, "Driver.lib" )
#pragma comment ( lib, "Resource.lib" )

#if defined(SKY_USE_D3D11)
#pragma comment ( lib, "DrvD3D11.lib" )
#endif

#endif

//-----------------------------------------------------------------------------
// External Libs
//-----------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
#pragma comment ( lib, "tinyxml.lib" )

#if defined(SKY_BUILD_DEBUG)
#pragma comment ( lib, "angelscriptd.lib" )
#else
#pragma comment ( lib, "angelscript.lib" )
#endif
#endif

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
class skyIApplication;
class skyApplicationSettings;
namespace skyConfig {
	class Vector3Type;
};
struct skyFileSettings;
struct skyCreateFileSettings;
struct sGfxRenderObject;
class skyIRenderer;
class skyIWindow;
class skyApplication;
class skyProcessible;
class skyProccessManager;
class skyModule;
class skyModuleManager;
class skyGfxModule;
class skyGfxManager;
class skyGfxRenderTechnique;
class skyGfxRenderPass;
class skyGfxDebugDrawManager;
class skyGfxCullingManager;
class skyImageFilter;
class skyImageEffect;
class skyImageFilterManager;
class skySceneImageFilter;
class skyDebugImageFilter;
class skyResourceManager;
class skyResource;
class skyResourceLoader;
class skyImageResource;
class skyImageUtils;
class skyShaderResource;
class skyEffectResource;
class skyShaderUtils;
class skyMeshResource;
class skyMeshUtils;
class skySubmeshResource;
class skyMaterialResource;
class skyMaterialUtils;
class skyGameObject;
class skyGameObjectPrefabResource;
class skyGameObjectPrefabUtils;
class skyIGameObjectComponent;
class skyGameObjectComponent;
class skyTransformComponent;
class skyCameraManager;
class skyICamera;
class skyPerspectiveCamera;
class skyConfigManager;
class skyConfig;

//-----------------------------------------------------------------------------
// Internal Include
//-----------------------------------------------------------------------------
#include "inc_engine_types.h"
#include "inc_engine_externs.h"
#include "inc_engine_helper.h"
#include "inc_engine_interfaces.h"
#include "Application\Config\skyConfigManager.h"
#include "Application\Config\skyConfig.h"
#include "Processing\skyProcessible.h"
#include "Processing\skyProcessManager.h"
#include "Application\Config\skyConfigVector3Type.h"
#include "Application\skyApplicationSettings.h"
#include "Application\skyIApplication.h"
#include "Application\skyApplication.h"
#include "Module\skyModule.h"
#include "Module\skyModuleManager.h"
#include "Graphics\Module\skyGfxModule.h"
#include "Graphics\System\skyGfxManager.h"
#include "Rendersystem\skyGfxRenderPass.h"
#include "Rendersystem\Culling\skyGfxCullingManager.h"
#include "Rendersystem\Debug\skyGfxDebugDrawManager.h"
#include "Postprocessing\skyImageFilter.h"
#include "Postprocessing\System\skyImageFilterManager.h"
#include "GameObject\skyGameObject.h"
#include "GameObject\skyGameObjectComponent.h"
#include "GameObject\Components\skyTransformComponent.h"
#include "GameObject\System\skyGameObjectManager.h"
#include "Camera\System\skyCameraManager.h"
#include "Camera\skyPerspectiveCamera.h"
#include "Resources\skyResource.h"
#include "ResourceSystem\skyResourceManager.h"
#include "ResourceSystem\skyResourceLoader.h"
#include "ResourceSystem\Loaders\skyMeshResourceLoader.h"
#include "ResourceSystem\Loaders\skyShaderResourceLoader.h"
#include "ResourceSystem\Loaders\skyImageResourceLoader.h"
#include "Resources\Image\skyImageResource.h"
#include "Resources\Image\skyImageUtils.h"
#include "Resources\Shader\skyShaderResource.h"
#include "Resources\Shader\skyEffectResource.h"
#include "Resources\Shader\skyShaderUtils.h"
#include "Resources\Mesh\skySubmeshResource.h"
#include "Resources\Mesh\skyMeshResource.h"
#include "Resources\Mesh\skyMeshUtils.h"
#include "Resources\Material\skyMaterialResource.h"
#include "Resources\Material\skyMaterialUtils.h"
#include "Resources\GameObject\skyGameObjectPrefabResource.h"
#include "Resources\GameObject\skyGameObjectPrefabUtils.h"

