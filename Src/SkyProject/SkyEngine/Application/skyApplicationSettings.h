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
// Name : skyApplicationSettings.h                                           //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Common Engine configuration structure. This struct takes a				 //
/// json file if you want to save more custom data add						 //
///	it to this struct														 //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyApplicationSettings (Class)
/// <summary>
/// Handles game options such as screen size, renderer, sound settings and so
/// on. 
/// </summary>
//-----------------------------------------------------------------------------
class skyApplicationSettings
{
public:

	//-------------------------------------------------------------------------
    // Public Methods
    //-------------------------------------------------------------------------
	static skyResult skyApplicationSettings::Load(std::string gameOptionFilePath);

};