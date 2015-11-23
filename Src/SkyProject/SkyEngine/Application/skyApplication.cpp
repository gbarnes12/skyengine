#include "stdafx.h"
#include "..\Rendersystem\skyGfxRenderTechnique.h"
#include "..\Graphics\System\skyGfxManager.h"
#include "skyApplication.h"

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
//#include "../Platform/Win32/skyGLWin32View.h"
#include "Platform//Win32/skyWindow.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// skyGameApplication Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyGameApplication (Constructor)
/// <summary>
/// Creates a new instance of the game application. 
/// </summary>
//-----------------------------------------------------------------------------
skyApplication::skyApplication(void)
	: m_eAppState(eApplicationState_Started)
	, pMesh(NULL)
{
}

//-----------------------------------------------------------------------------
//  Name : VInitialize (Virtual Function)
/// <summary>
/// Initializes all the necessary subsystems among them are logger, game options
/// renderer etc. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyApplication::VInitialize()
{
	//-----------------------------------------------------------------------------
	// Enable logs
	//-----------------------------------------------------------------------------
	skyLog::g_FileLog.VEnable();
	skyLog::g_HTMLLog.VEnable();

	skyResult hr;

	// initialize the Resource system
	//SKY_VR(skyResourceManager::Initialize(500));


	// initialize the runtime class system thus all the runtimestuff will be loaded
	// automatically!
	//skySingleton<skyGfxModule>::Instance();
	//SKY_VR(skyRuntimeClass::StaticInitialize());

	//skyApplicationSettings::Load( skyConfig::g_configPath );
	// central element of all the managers that need to get initialized 
	// part for part. Managers get initialized by their respective levels!
	SKY_VR(skyModuleManager::Instance().Initialize());

	// Initialize our camera manager / admin
	//SKY_VR(skyCameraManager::Initialize());

	skyConfigClass<skyBool> mTest("\\Game\\Test", true);
	mTest = false;

	// add the image filters to the application!
	// this should be data driven or what ever at some point ;)
	/*skySceneImageFilter* pSceneFilter = SKY_NEW skySceneImageFilter();
	pSceneFilter->SetActive(true);
	skyImageFilterManager::AddFilter(pSceneFilter);

	skyDebugImageFilter* pDebugFilter = SKY_NEW skyDebugImageFilter();
	pDebugFilter->SetActive(true);
	skyImageFilterManager::AddFilter(pDebugFilter);*/
	
	//skyGameObject* pObject = nullptr;
	//skyGameObjectManager::CreateGameObject(INVALID_GAMEOBJECT_ID, "Test", &pObject);

	//skyGameObjectPrefab* pPrefab = nullptr;
	//skyGameObjectPrefabUtils::Load("Test.goprefab", &pPrefab);

	//skyMeshUtils::Load("Cube.sm", &pMesh);
	//pMesh->AddRef();
	//skyMeshUtils::Request(pMesh, eResourceRequestMode_Immediate);

	/*
	skyImageResource* pResource2 = nullptr;
	sGfxTextureDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sGfxTextureDesc));
	sDesc.m_uiWidth = 1024;
	sDesc.m_uiHeight = 1024;
	sDesc.m_eFormat = eGfxTextureFormat_R32G32B32A32_FLOAT;
	sDesc.m_eUsage = eGfxUsage_Dynamic;
	sDesc.m_uiBindFlags = eGfxBindFlags_ShaderResource;
	sDesc.m_uiCPUFlags = eGfxCpuAccessFlags_Write;
	sDesc.m_sSample.m_uiCount = 1;
	sDesc.m_sSample.m_uiQuality = 0;
	sDesc.m_uiArraySize = 1;
	sDesc.m_uiMipLevels = 1;

	skyImageUtils::Create(sDesc, &pResource2);*/

	return SKY_OK;
}


//-----------------------------------------------------------------------------
//  Name : VLoad (Virtual Function)
/// <summary>
/// Loads the game. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyApplication::VLoad(void)
{
	return SKY_OK;
}


//-----------------------------------------------------------------------------
//  Name : VRun (Function)
/// <summary>
/// Runs the whole game loop.
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyApplication::VRun(void)
{
	// once everything is fine we can proceed with the game loop!
	// first we need to set the isRunning variable to true.
	this->m_eAppState = eApplicationState_Running;

	//skyComPtr<skyIWindow> pWindow (skyGfxManager::Window());
	
	//if(!pWindow)
	//	return SKY_INVALID_POINTER;

	
	//while(m_eAppState == eApplicationState_Running)
	//{
		//if(pWindow->VPeekMessages())
		//	m_eAppState = eApplicationState_Stopping;

		//if(pMesh)
		//	pMesh->Draw();
		
		//SKY_ADD_LINE(skyVector4(0, 0, 0, 0), skyVector4(4, 4, 0, 1), skyColor(0.0f, 0.0f, 1.0f, 1.0f));
		//SKY_ADD_TRIANGLE(skyVector4(0, 0, 0, 0),  skyColor(1.0f, 1.0f, 1.0f, 1.0f));

		//skyProcessManager::Instance().Process();
	//}
	
	SKY_RELEASE(pMesh);

	this->m_eAppState = eApplicationState_Stopping;

	return SKY_OK;
}



//-----------------------------------------------------------------------------
//  Name : VDispose (Function)
/// <summary>
/// Takes care of freeing all the registered memory of the subsystems.
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyApplication::VDispose(void)
{
	skyResult hr;
	//SKY_VR(skyCameraManager::Shutdown());
	//SKY_VR(skyResourceManager::Shutdown());
	skyModuleManager::Instance().Shutdown();
	this->m_eAppState = eApplicationState_Stopped;
	return SKY_OK;
}