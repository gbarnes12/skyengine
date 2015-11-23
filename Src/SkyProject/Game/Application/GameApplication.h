#pragma once
//---------------------------------------------------------------------------//
//				___________     __   ___  ___      ___                       //
//				|  _______ \   |  | /  /  \  \    /  /                       //
//				|  |           |  |/  /    \  \  /  /                        //
//				|  |_______    |     /      \  \/  /                         //
//				\_________ \   |     |       \    /                          //
//				  _		 |  |  |  |\  \       |  |                           //
//				 | \_____|  |  |  | \  \      |  |                           //
//				 |__________/  |__|  \__\     |__|  Engine.                  //
//                                                                           //
//---------------------------------------------------------------------------//
//                                                                           //
// Name : skyGameApplication.h                                               //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Base Game Application class. Inherit from it to create your own			 //
///	Game Application. It takes care of successfully initializing			 //
/// every subsystem.														 //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "..\SkyEngine\Application\skyApplication.h"

//-----------------------------------------------------------------------------
// ForwarDeclaration
//-----------------------------------------------------------------------------
class skyBaseGameLogic;

class GameApplication : public skyApplication 
{
public:
	virtual skyResult GameApplication::VInitialize();
};

