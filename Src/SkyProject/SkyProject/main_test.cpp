/*#include <iostream>
#include "inc_driver.h"
#include "inc_drvd3d11.h"
#include "inc_engine.h"


#if defined(SKY_BUILD_DEBUG)
#pragma comment(lib, "Driver_D.lib")
#pragma comment(lib, "DrvD3D11_D.lib")
#pragma comment(lib, "Engine_D.lib")
#else
#pragma comment(lib, "Driver.lib")
#pragma comment(lib, "DrvD3D11.lib")
#endif


int main()
{
	//-----------------------------------------------------------------------------
	//  Memory Leak Checking!
	//-----------------------------------------------------------------------------
	// Set up checks for memory leaks.
    // Game Coding Complete reference - Chapter 21, page 834
    // Only activate this when we are within the debug build!
	#if defined(SKY_BUILD_DEBUG) | defined(SKY_BUILD_DEBUG)
	_CrtDumpMemoryLeaks();

    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	
	#endif

	skyBool bIsRunning = true;
	skyWindow* pWindow = nullptr;
	skyIGfxSystem* pSystem = nullptr;
	skyIGfxDevice* pDevice = nullptr;
	skyIGfxRenderTarget* pBackBufferRT = nullptr;
	skyIGfxTexture* pBackBufferTexture = nullptr;
	skyIGfxShader* pVertexShader = nullptr;
	skyIGfxShader* pPixelShader = nullptr;
	sGfxDeviceDesc sDesc;
	sGfxPresentDesc sPDesc;

	pWindow = SKY_NEW skyWindow();
	pWindow->VInitialize(L"test", 800, 600, false, 32, 32, 8);
	pWindow->VCreate();


	skyResult hr = skyCreateGfxSystem(&pSystem);
	if(hr != SKY_OK)
		return -1;

	SKY_ZERO_MEM(&sDesc, sizeof(sGfxDeviceDesc));
	sDesc.m_bWindowed = true;
	sDesc.m_uiWidth = 800;
	sDesc.m_uiHeight = 600;
	sDesc.m_eFormat = eGfxTextureFormat_R8G8B8A8_UNORM;
	sDesc.m_pHandle = pWindow->VGetHwnd();

	SKY_ZERO_MEM(&sPDesc, sizeof(sGfxPresentDesc));
	sPDesc.m_uiSyncInterval = 0;

	/*
	DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Device Creation");
	hr = pSystem->CreateDevice(sDesc, &pDevice);
	if(hr != SKY_OK)
		return -1;

	hr = pDevice->GetBackBuffer(&pBackBufferTexture);
	if(hr != SKY_OK)
		return -1;

	hr = pDevice->CreateRenderTarget(&pBackBufferRT, pBackBufferTexture);
	if(hr != SKY_OK)
		return -1;
	DX_END_SECTION();
	


	skyGfxManager::Initialize();
	skyGfxDebugDrawManager::Instance().Initialize();

	while(bIsRunning)
	{
		if(pWindow->VPeekMessages())
		{
			bIsRunning = false;
		}

		DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Frame Rendering");
		pDevice->SetRenderTarget(0, pBackBufferRT );
		pDevice->ClearRenderTarget(0, sGfxColor(0.5f, 0.5f, 0.5f, 1.0f));

		DX_START_SECTION(skyColor(1.0f, 0.0f, 0.0f, 1.0f), L"Debug Manager");
		skyGfxDebugDrawManager::Instance().Prepare();
		DX_END_SECTION();

		pDevice->Present(sPDesc);
		DX_END_SECTION();
	}
	
	skyGfxDebugDrawManager::Instance().Shutdown();

	SKY_SAFE_DELETE(pSystem);
	SKY_SAFE_DELETE(pWindow);
	return 0;
}*/