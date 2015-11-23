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
// Name : skyFileSystem.h                                                    //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The file system takes care of connecting the file devices together thus  //
/// they can be piggybacked onto each other. Furthermore it is used          //
/// in order to open a file with a given mode and close it again.            //
/// File handling will be passed on to the mounted and specified devices.    //
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
//  Name : skyFileSystem (Class)
/// <summary>
/// Is used to access files platform independent and in a convinient way. 
/// You need to mount all the file devices to the system in order to open 
/// a file with those devices. 
/// </summary>
//-----------------------------------------------------------------------------
class skyFileSystem
{
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	friend class skyZipFileDevice;
	typedef std::map<std::string, skyIFileDevice*> skyMountedDeviceMap;
public:
	//-------------------------------------------------------------------------
    // Public Members
    //-------------------------------------------------------------------------
	

	//-------------------------------------------------------------------------
    // Public Methods
    //-------------------------------------------------------------------------
	void skyFileSystem::Mount ( skyIFileDevice* pDevice );
	void skyFileSystem::Unmount ( skyIFileDevice* pDevice );

	//-------------------------------------------------------------------------
    // Synchronous Methods
    //-------------------------------------------------------------------------
	skyIFile* skyFileSystem::Open ( std::string deviceList, std::string filePath, skyFileMode mode );
	void skyFileSystem::Close ( skyIFile* pFile );

private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	skyMountedDeviceMap mMountedDevices;
	std::vector<std::string> mDeviceOrder;
	unsigned int mLastDeviceIndex;

	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	void skyFileSystem::SplitDeviceList ( std::string list );
	skyIFileDevice* skyFileSystem::GetNextDevice ();
};