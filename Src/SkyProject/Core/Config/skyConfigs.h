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
// Name : skyConfigs.h														 //
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


namespace skyConfig
{
	extern IntType g_windowHeight;	
	extern IntType g_windowWidth;
	extern IntType g_windowDepthBits;
	extern IntType g_windowColorBits;
	extern IntType g_windowAlphaBits;
	extern BoolType g_windowIsFullscreen;
	extern StringType g_windowTitle;
	extern BoolType g_IsDebugMode;
	extern StringType g_assetDirectory;
	extern FloatType g_screenRefreshRate;
	extern BoolType g_useMultiSampling;
	extern BoolType g_showFPS;
	extern IntType g_sampleCount;
	extern BoolType g_deferredDebugMode;
};