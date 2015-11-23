#pragma once
//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------
#include "skyIApplication.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyApplication (Class)
/// <summary>
/// A game application is the main entry point of your game and therefore 
/// needs to be inherited in your game project. There are several virtual 
/// functions in order to provide your own logic. The base class takes care
/// of initializing all the subystems required in order to run the game. 
/// </summary>
//-----------------------------------------------------------------------------
class skyApplication : public skyIApplication
{
public:

	//-------------------------------------------------------------------------
    // Constructors & Destructors
    //-------------------------------------------------------------------------
	skyApplication::skyApplication(skyVoid);

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual skyResult skyApplication::VInitialize();
	virtual skyResult skyApplication::VLoad(skyVoid);
	virtual skyResult skyApplication::VRun(skyVoid);
	virtual skyResult skyApplication::VDispose(skyVoid);

protected:
	//-------------------------------------------------------------------------
    // Protected Members
    //-------------------------------------------------------------------------
	eApplicationState m_eAppState;
	shared_ptr<skyIWindow> m_pWindowView;
	skyTimer m_bGameTimer;
	skyMeshResource* pMesh;
};

//-------------------------------------------------------------------------
// Global Stuff
//-------------------------------------------------------------------------


