#pragma once
#include "..\SkyEngine\Application\skyIApplication.h"
#include "..\SkyEngine\Graphics\skyIRenderer.h"
#include "..\SkyEngine\Utils\skyTimer.h"

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------
class skyResourceSystem;
class skyIRenderer;
class skyScriptSystem;
class skyBaseGameLogic;


//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyEditorApplication (Class)
/// <summary>
/// The editor application is the main entry point of your editor.
/// There are several virtual functions in order to provide your own logic. 
/// The base class takes care of initializing all the subystems required in order to run the game. 
/// </summary>
//-----------------------------------------------------------------------------
class skyEditorApplication : public skyIApplication
{
public:
	//-----------------------------------------------------------------------------
	// Public enumeration
	//-----------------------------------------------------------------------------
	enum skyApplicationState 
	{
		SKY_INITIALIZED,
		SKY_LOADING,
		SKY_RUNNING,
		SKY_STOPPING,
		SKY_STOPPED
	};


	//-------------------------------------------------------------------------
    // Constructors & Destructors
    //-------------------------------------------------------------------------
	skyEditorApplication::skyEditorApplication(skyVoid);

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual skyResult skyEditorApplication::VInitialize(std::string ConfigFile);
	virtual skyResult skyEditorApplication::VLoad(skyVoid);
	virtual skyResult skyEditorApplication::VRun(skyVoid);
	virtual skyResult skyEditorApplication::VDispose(skyVoid);
	//virtual void skyGameApplication::VRegisterResourceLoaders(void);
	virtual skyBaseGameLogic* skyEditorApplication::VCreateGameAndView(skyVoid);
	

	//-------------------------------------------------------------------------
    // Public Methods
    //-------------------------------------------------------------------------
	shared_ptr<skyIRenderer> skyEditorApplication::GetRenderer(skyVoid) { return this->pRenderer; }
	skyBaseGameLogic* skyEditorApplication::GetLogic(skyVoid) { return SKY_NULL; }
	skyTimer* skyEditorApplication::GetGameTime(skyVoid) { return &this->mGameTimer; }
	skyProfiler* skyEditorApplication::GetProfiler(skyVoid) { return SKY_NULL; }
	shared_ptr<skyApplicationDispatcher> skyEditorApplication::GetDispatcher(skyVoid) { return this->pDispatcher; }
	void skyEditorApplication::RegisterRenderer ( skyIRenderer::SharedPtr pRenderer );

protected:
	//-------------------------------------------------------------------------
    // Protected Members
    //-------------------------------------------------------------------------
	skyApplicationState mCurrentApplicationState;
	shared_ptr<skyApplicationDispatcher> pDispatcher;
	shared_ptr<skyIRenderer> pRenderer;
	shared_ptr<skyScriptSystem> pScriptSystem;
	skyBool mIsRunning;
	skyTimer mGameTimer;
	HWND mHWND;

	//-------------------------------------------------------------------------
    // Protected virtual Mthods
    //-------------------------------------------------------------------------
	virtual skyResult skyEditorApplication::VRender (skyVoid);
};