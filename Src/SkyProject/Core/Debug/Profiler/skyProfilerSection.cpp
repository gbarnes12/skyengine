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
// Name : skyProfilerSection.cp                                              //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// A specific contained section in the profiler this could represent        //
/// a specific method or area within the engine e.g.: Renderer.PreRender()   //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//---------------------------------------------------------------------------//

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyProfilerSection.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyProfilerSection (Class)
/// <summary>
/// Interface which every log class needs to inherit from. You need to   
/// provide your own functionality for the Log methods.
/// </summary>
//-----------------------------------------------------------------------------
skyProfilerSection::skyProfilerSection(std::string name) 
{
	pTimer = SKY_NEW skyTimer();
	this->mName = name;
}

skyProfilerSection::~skyProfilerSection()
{
	pTimer->Update();
	float time = pTimer->TotalTime();
	/*skyProfiler* pProfiler = g_gameApplication->GetProfiler();
	if(pProfiler) {
		pProfiler->CountSection(this->mName, time);
	}*/
	SKY_SAFE_DELETE(pTimer);
}

std::string skyProfilerSection::GetName()
{
	return this->mName;
}