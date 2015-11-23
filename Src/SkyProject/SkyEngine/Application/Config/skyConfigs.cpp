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
// Name : skyConfigs.cpp													 //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// This file contains all the globalg config variables on the global        //
/// stack. There are three types: IntType, BoolType and FloatType.           //
/// Those global values will add themself to an intrusive list.              //
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
#include "stdafx.h"
#include "skyConfigs.h"

namespace skyConfig
{
	Vector3Type g_cameraPosition("CameraPosition", "Where is the camera?", skyVector3(0.0f, 0.0f, 0.0f));
	Vector3Type g_cameraLookAt("CameraLookAt", "What does the camera look at", skyVector3(0.0f, 0.0f, 0.0f));
};