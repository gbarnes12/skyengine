#include "Stdafx.h"
#include "skyEditorApplication.h"
#include "..\SkyEngine\Graphics\skyDeferredRenderer.h"
#include "..\SkyEngine\EventSystem\Dispatchers\Application\skyApplicationDispatcher.h"


///////////////////////////////////////////////////////////////////////////////
// skyEditorApplication Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyEditorApplication (Constructor)
/// <summary>
/// Creates a new instance of the game application. 
/// </summary>
//-----------------------------------------------------------------------------
skyEditorApplication::skyEditorApplication(skyVoid) 
{
	this->mIsRunning = false;
}

//-----------------------------------------------------------------------------
//  Name : VInitialize (Virtual Function)
/// <summary>
/// Initializes all the necessary subsystems among them are logger, game options
/// renderer etc. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyEditorApplication::VInitialize(std::string ConfigFile)
{
	//-----------------------------------------------------------------------------
	// Enable logs
	//-----------------------------------------------------------------------------
	skyLog::g_FileLog.VEnable();
	skyLog::g_HTMLLog.VEnable();

	g_appMode = SKY_EDITOR;

	//-----------------------------------------------------------------------------
	// Initialize skyResourceSystem
	//-----------------------------------------------------------------------------
	this->pResourceSystem = shared_ptr<skyResourceSystem>(SKY_NEW skyResourceSystem(2000));
	if(this->pResourceSystem->Initialize () == SKY_ERROR)
	{
		long line = __LINE__;
		SKY_CRITICAL_ERROR(skyLogChannel::TXT_FILE, "skyGameApplication: Couldn't initialize application resource system file at line " + skyToString(line));

		return SKY_ERROR;
	}

	//-----------------------------------------------------------------------------
	// Initialize NetworkLog
	//-----------------------------------------------------------------------------
	/*skyLog::g_NetworkLog.Initialize();
	skyLog::g_NetworkLog.VEnable();
	skyLog::g_NetworkLog.VWrite(skyLogLevel::INFO, "Test");*/

	/*
	//-----------------------------------------------------------------------------
	// Initialize GraphicsDevice
	//-----------------------------------------------------------------------------
	skyResult hr;
	hr = skyGraphicsDevice::Spawn(SKY_NULL, mHWND, &g_GfxDevice);
	if ( hr != SKY_OK ) 
	{
		skySafeDelete(g_GfxDevice);
		return SKY_ERROR;
	}


	//-----------------------------------------------------------------------------
	// Initialize Renderer
	//-----------------------------------------------------------------------------
	skyIRenderer::SharedPtr pRenderer = nullptr;
	pRenderer = shared_ptr<skyIRenderer>(SKY_NEW skyDeferredRenderer());
	
	if(pRenderer->VInitialize() == SKY_ERROR )
	{
		SKY_PRINT_CONSOLE("skyGameApplication", "couldn't create DirectX Context.", 0x0D);
		SKY_FATAL_ERROR(skyLogChannel::TXT_FILE, "skyDXWin32View: couldn't create DirectX Context.");
		return SKY_ERROR;
	}

	this->RegisterRenderer(pRenderer);
	*/

	//-----------------------------------------------------------------------------
	// Initialize skyApplicationDispatcher
	//-----------------------------------------------------------------------------
	this->pDispatcher = shared_ptr<skyApplicationDispatcher>(SKY_NEW skyApplicationDispatcher());

	return SKY_OK;
}


 skyResult skyEditorApplication::VLoad(skyVoid)
 {
	 return SKY_OK;
 }

skyResult skyEditorApplication::VRun(skyVoid)
{
	if(this->pRenderer) {
		this->pRenderer->VPreRender ();
		this->pRenderer->VPostRender ();
	}

	// process the application dispatcher for 8 ms
	if(this->pDispatcher)
		this->pDispatcher->VUpdate ( 8 );

	mGameTimer.Update();

	return SKY_OK;
}

//-----------------------------------------------------------------------------
//  Name : VDispose (Function)
/// <summary>
/// Takes care of freeing all the registered memory of the subsystems.
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyEditorApplication::VDispose(void)
{
	if(pDispatcher) {
		skyEventPtr onExitEvent = skyEventPtr(SKY_NEW skyApplicationEvents::OnExitEvent());
		this->pDispatcher->VQueueEvent(onExitEvent);
	}

	return SKY_OK;
}
	
skyBaseGameLogic* skyEditorApplication::VCreateGameAndView(skyVoid)
{
	return nullptr;
}

void skyEditorApplication::RegisterRenderer ( skyIRenderer::SharedPtr pRenderer )
{
	this->pRenderer = pRenderer;
}

skyResult skyEditorApplication::VRender (skyVoid)
{
	return SKY_OK;
}