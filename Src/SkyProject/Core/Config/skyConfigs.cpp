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
	IntType g_windowHeight ("WindowHeight", "Height of the window", 768, 32, 2048);
	IntType g_windowWidth  ("WindowWidth", "Width of the window.", 1024, 32, 2048);
	IntType g_windowDepthBits ("WindowDepthBits", "Depth bits of window", 32, 16, 32);
	IntType g_windowColorBits ("WindowColorBits", "Color bits of window", 32, 16, 32);
	IntType g_windowAlphaBits ("WindowAlphaBits", "Alpha bits of window", 8, 8, 8);
	BoolType g_windowIsFullscreen ("WindowIsFullscreen", "Is the window in fullscreen mode?", false);
	StringType g_windowTitle ("WindowTitle", "The title of the window", "skyEngine Window");
	BoolType g_IsDebugMode ("IsDebugMode", "Is the engine in debug mode?", true);
	StringType g_assetDirectory ("AssetDirectory", "Directory where we can find the assets?", "../../../Assets/");
	FloatType g_screenRefreshRate ("ScreenRefreshRate", "How often does the screen get refreshed?", 1000/60);
	BoolType g_useMultiSampling ("UseMultiSampling", "Does this application use Multi Sampling?", false);
	BoolType g_showFPS ("ShowFPS", "Show the FPS for the programm?", true);
	IntType g_sampleCount ("SampleCount", "How many samples do we use?", 1);
	BoolType g_deferredDebugMode("DeferredDebugMode", "Use the deferred debug mode. This will show content of gbuffer", SKY_TRUE);
};