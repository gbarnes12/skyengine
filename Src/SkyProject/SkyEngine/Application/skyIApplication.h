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
// Name : skyIApplication.h                                                  //
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

class skyIApplication 
{
public:
	virtual skyResult skyIApplication::VInitialize() = 0;
	virtual skyResult skyIApplication::VLoad(skyVoid) = 0;
	virtual skyResult skyIApplication::VRun(skyVoid) = 0;
	virtual skyResult skyIApplication::VDispose(skyVoid) = 0;
};
