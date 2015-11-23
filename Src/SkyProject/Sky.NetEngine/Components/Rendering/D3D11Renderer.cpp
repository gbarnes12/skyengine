// This is the main DLL file.
#include "Stdafx.h"
#include "..\SkyEngine\Graphics\skyGraphicsDevice.h"
#include "..\SkyEngine\Graphics\skyDeferredRenderer.h"
#include "..\SkyEngine\Application\Config\skyConfigs.h"
#include "..\SkyEngine\Application\skyGameApplication.h"
#include "D3D11Renderer.h"

using namespace Sky::NetEngine::Components::Rendering;


skyBool D3D11Renderer::Spawn ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight, D3D11Renderer^% pRenderer )
{
	skyConfig::g_windowWidth = (int)a_iClientWidth;
	skyConfig::g_windowHeight = (int)a_iClientHeight;
	//skyConfig::g_deferredDebugMode = SKY_TRUE;

	D3D11Renderer^ pManagedRenderer = nullptr;
	shared_ptr<skyIRenderer> pInternalRenderer;
	skyResult hr;


	hr = skyGraphicsDevice::Spawn(SKY_NULL, (HWND)a_pWindow, &g_GfxDevice);
	if ( hr != SKY_OK ) 
	{
		skySafeDelete(g_GfxDevice);
		return false;
	}

	pInternalRenderer =  shared_ptr<skyIRenderer>(SKY_NEW skyDeferredRenderer());
	hr = pInternalRenderer->VInitialize();
	if ( hr != SKY_OK ) 
	{
		skySafeDelete(g_GfxDevice);
		return false;
	}

	if(g_gameApplication)
	{
		g_gameApplication->RegisterRenderer(pInternalRenderer);
	}


	pManagedRenderer = gcnew D3D11Renderer(pInternalRenderer);
	pRenderer = pManagedRenderer;

	return true;
}

D3D11Renderer::D3D11Renderer ( shared_ptr<skyIRenderer>& a_pRenderer )
	: m_pRenderer(new shared_ptr<skyIRenderer>(a_pRenderer))
{
	
}

D3D11Renderer::~D3D11Renderer()
{
	if((*m_pRenderer))
	{
		(*m_pRenderer)->VDispose();
	}

	if(g_GfxDevice) {
		g_GfxDevice->VDispose();
		skySafeDelete(g_GfxDevice);
	}

}