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
// Name : skyIFileDevice.h                                                   //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// File devices can be piggybacked onto other file devices, if they need    //
/// to. And are used responsible to return the proper file interface.        //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyIFileDevice (Interface)
/// <summary>
/// Used to secure that every file device implements the needed methods and 
/// functionality. A file device is used in order to open the a file and 
/// return the correct file type such as NetworkFile by the NetworkDevice. 
/// </summary>
//-----------------------------------------------------------------------------
class skyIFileDevice 
{
	friend class skyFileSystem;

public:
	//-----------------------------------------------------------------------------
	// Constructor & Destructor
	//-----------------------------------------------------------------------------
	skyIFileDevice::skyIFileDevice ( std::string name ) 
	{ 
		this->mName = name; 
	}
	virtual skyIFileDevice::~skyIFileDevice() { }

	//-----------------------------------------------------------------------------
	// Public Virtual Methods
	//-----------------------------------------------------------------------------
	virtual skyIFile* skyIFileDevice::VOpen (std::string filePath, unsigned int fileMode, skyFileSystem* fileSystem = nullptr) = 0;
private:
	//-----------------------------------------------------------------------------
	// Private Members
	//-----------------------------------------------------------------------------
	std::string mName;
};