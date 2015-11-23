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
// Name : skyProfilerSection.h                                               //
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
#define SKY_PROFILE(name) skyProfilerSection __section(name);

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
class skyProfilerSection 
{
public:
	skyProfilerSection::skyProfilerSection(std::string name);
	skyProfilerSection::~skyProfilerSection(); 

	std::string skyProfilerSection::GetName();

private:
	skyTimer* pTimer;
	std::string mName;
};