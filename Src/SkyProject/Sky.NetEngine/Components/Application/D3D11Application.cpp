//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------
#include "Stdafx.h"
#include "..\SkyEngine\Application\skyGameApplication.h"
#include "skyEditorApplication.h"
#include "..\Rendering\D3D11Renderer.h"
#include "D3D11Application.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
using namespace Sky::NetEngine::Components::Application;
using namespace Sky::NetEngine::Components::Rendering;

skyBool D3D11Application::Spawn ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight,  D3D11Application^% pApplication )
{
	D3D11Application^ pManagedApplication = nullptr;

	g_gameApplication = SKY_NEW skyEditorApplication ( );
	if ( g_gameApplication->VInitialize ( "" ) != SKY_OK )
	{
		g_gameApplication->VDispose();
		skySafeDelete(g_gameApplication);
		return SKY_FALSE;
	}

	pManagedApplication = gcnew D3D11Application( a_pWindow, a_iClientWidth, a_iClientHeight );
	if(!pManagedApplication->Initialize())
	{
		g_gameApplication->VDispose();
		skySafeDelete(g_gameApplication);
		return SKY_FALSE;
	}

	pApplication = pManagedApplication;

	return SKY_TRUE;
}

D3D11Application::D3D11Application ( skyInt a_pWindow, skyUInt a_iClientWidth, skyUInt a_iClientHeight ) 
{
	this->m_iHWND = a_pWindow;
	this->m_uiWidth = a_iClientWidth;
	this->m_uiHeight = a_iClientHeight;
}

D3D11Application::~D3D11Application()
{
	if(g_gameApplication) 
		g_gameApplication->VDispose();

	skySafeDelete(g_gameApplication);
}


D3D11Renderer^ D3D11Application::GetRenderer ( skyVoid )
{
	return this->m_pManagedRenderer;
}

skyBool D3D11Application::Initialize ( skyVoid )
{
	return D3D11Renderer::Spawn(this->m_iHWND, this->m_uiWidth, this->m_uiHeight, this->m_pManagedRenderer);
}

skyVoid D3D11Application::Run ( skyVoid )
{
	if(g_gameApplication) 
	{
		g_gameApplication->VRun ( );
	}
}


skyVoid D3D11Application::Resize ( skyUInt a_iWidth, skyUInt a_iHeight )
{
	if(g_gameApplication) 
	{
		shared_ptr<skyIRenderer> pRenderer = g_gameApplication->GetRenderer();
		if(pRenderer) 
		{
			skyConfig::g_windowWidth = (skyInt)a_iWidth;
			skyConfig::g_windowHeight = (skyInt)a_iHeight;
			pRenderer->VResize(a_iWidth, a_iHeight);
		}
	}
}