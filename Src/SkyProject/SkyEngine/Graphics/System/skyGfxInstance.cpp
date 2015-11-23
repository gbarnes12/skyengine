#include "stdafx.h"
#include "skyGfxInstance.h"

sGfxDeviceDesc g_sDeviceDesc;



skyGfxInstance::skyGfxInstance()
	: m_pWindow(NULL)
	, m_pDevice(NULL)
	, m_pSystem(NULL)
	, m_pBackBufferTexture(NULL)
	, m_pBackBufferRT(NULL)
{
}

skyResult skyGfxInstance::Initialize ( skyVoid )
{
	skyResult hr;

	// Ensure that the Module is running
	// we need to call this at least once somewhere in code!
	SKY_TODO("find another way to make sure we don't need this");
	//SKY_ENSURE_MODULE(skyGfxModule);

	m_pWindow = SKY_NEW skyWindow();
	SKY_VR(m_pWindow->VInitialize(skyToWString("Game [Version 1.0.1.83] - Built on 11.01.2013 02:05")
								, skyConfig::g_windowWidth
								, skyConfig::g_windowHeight
								, skyConfig::g_windowIsFullscreen
								, skyConfig::g_windowColorBits
								, skyConfig::g_windowDepthBits
								, skyConfig::g_windowAlphaBits
								));

	SKY_VR(m_pWindow->VCreate());

	// create system!
	SKY_VR(skyCreateGfxSystem(&m_pSystem));

	SKY_ZERO_MEM(&g_sDeviceDesc, sizeof(sGfxDeviceDesc));
	g_sDeviceDesc.m_bWindowed = !skyConfig::g_windowIsFullscreen;
	g_sDeviceDesc.m_uiWidth = skyConfig::g_windowWidth;
	g_sDeviceDesc.m_uiHeight = skyConfig::g_windowHeight;
	g_sDeviceDesc.m_eFormat = eGfxTextureFormat_R8G8B8A8_UNORM;
	g_sDeviceDesc.m_pHandle = m_pWindow->VGetHwnd();

	SKY_VR(m_pSystem->CreateDevice(g_sDeviceDesc, &m_pDevice));

	// Create Backbuffer Stuff!
	SKY_VR(m_pDevice->GetBackBuffer(&m_pBackBufferTexture));
	SKY_VR(m_pDevice->CreateRenderTarget(&m_pBackBufferRT, m_pBackBufferTexture));

	// set viewport 
	sGfxViewport sViewport;
	SKY_ZERO_MEM(&sViewport, sizeof(sGfxViewport));
	sViewport.m_fWidth = skyConfig::g_windowWidth;
	sViewport.m_fHeight = skyConfig::g_windowHeight;
	sViewport.m_fTopLeftX = 0;
	sViewport.m_fTopLeftY = 0;
	sViewport.m_fMinDepth = 0.0f;
	sViewport.m_fMaxDepth = 1.0f;
	m_pDevice->SetViewport(sViewport);

	sGfxConstantDesc sDesc;
	SKY_ZERO_MEM(&sDesc, sizeof(sGfxConstantDesc));
	sDesc.m_eUsage = eGfxUsage_Dynamic;
	sDesc.m_eBindFlags = eGfxBindFlags_ConstantBuffer;
	sDesc.m_eCPUAccess = eGfxCpuAccessFlags_Write;
	sDesc.m_uiCount = 1;
	sDesc.m_uiSize = sizeof(sMatrixBuffer);

	skyGfxManager::CreateConstantBuffer(&m_pMatrixBuffer, sDesc);

	return SKY_OK;
}

skyResult skyGfxInstance::Shutdown ( skyVoid )
{
	SKY_SAFE_DELETE(m_pMatrixBuffer);
	SKY_SAFE_DELETE(m_pBackBufferRT);
	SKY_SAFE_DELETE(m_pBackBufferTexture);
	SKY_SAFE_DELETE(m_pSystem);
	SKY_SAFE_DELETE(m_pWindow);
	return SKY_OK;
}