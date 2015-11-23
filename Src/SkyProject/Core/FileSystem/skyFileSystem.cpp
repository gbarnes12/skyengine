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
// Name : skyFileSystem.cpp                                                  //
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
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyFileSystem.h"

///////////////////////////////////////////////////////////////////////////////
// skyFileSystem Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : Mount (Method)
/// <summary>
/// Mounts a file device to the file system. If the device already has been 
/// mounted to the system you will receive a message in debug mode.
/// </summary>
//-----------------------------------------------------------------------------
void skyFileSystem::Mount ( skyIFileDevice* pDevice )
{
	if(pDevice)
	{
		skyMountedDeviceMap::iterator it = mMountedDevices.find(pDevice->mName);

		if(it == mMountedDevices.end())
		{
			mMountedDevices.insert(std::pair<std::string, skyIFileDevice*>(pDevice->mName, pDevice));
		}
	}
}

//-----------------------------------------------------------------------------
//  Name : Unmount (Method)
/// <summary>
/// Unmounts a specific file device again. You don't have to use this in order
/// to destroy the file device. This method will only erase the device from 
/// an internal device list.
/// </summary>
//-----------------------------------------------------------------------------
void skyFileSystem::Unmount ( skyIFileDevice* pDevice )
{
	if(pDevice)
	{
		skyMountedDeviceMap::iterator it = mMountedDevices.find(pDevice->mName);

		if(it != mMountedDevices.end())
		{
			mMountedDevices.erase(it);
		}
	}
}

//-----------------------------------------------------------------------------
//  Name : Open (Method)
/// <summary>
/// Opens a file. You need to specify the devices you want to use. Each device
/// has an unique name identifier. Example: In order to load a encrypted file
/// from hdd you would supply crypted:disk as the device list. Furthermore 
/// you need to specify a valid file path and mode. Modes can be the following:
/// MODE_READ, MODE_WRITE, MODE_RECREATE, MODE_APPEND, MODE_BINARY, MODE_ASCII
/// The modes can be combined for example: MODE_READ | MODE_BINARY. 
/// </summary>
//-----------------------------------------------------------------------------
skyIFile* skyFileSystem::Open ( std::string deviceList, std::string filePath, skyFileMode mode )
{
	if(mMountedDevices.size() > 0)
	{
		this->mDeviceOrder.clear();
		this->mLastDeviceIndex = 0;

		this->SplitDeviceList(deviceList);

		if(this->mDeviceOrder.size() > 0)
		{
			// retrieve our current device name!
			std::string deviceName = this->mDeviceOrder[mLastDeviceIndex];
			skyMountedDeviceMap::iterator it = mMountedDevices.find(deviceName);

			if(it != mMountedDevices.end())
			{
				return it->second->VOpen(filePath, mode, this);
			}
		}
	
	}

	return nullptr;
}


//-----------------------------------------------------------------------------
//  Name : Close (Method)
/// <summary>
/// Deletes the file pointer again and therefore takes care of destructing 
/// the file. Please make sure to use this to avoid any memory leaks. 
/// </summary>
//-----------------------------------------------------------------------------
void skyFileSystem::Close ( skyIFile* pFile )
{
	if(pFile)
	{
		SKY_SAFE_DELETE(pFile);
	}
}

//-----------------------------------------------------------------------------
//  Name : GetNextDevice (Method)
/// <summary>
/// Returns the next device in the list of specified devices whenever a user
/// wans to open a file.
/// </summary>
//-----------------------------------------------------------------------------
skyIFileDevice* skyFileSystem::GetNextDevice ()
{
	if((mLastDeviceIndex+1) <= mDeviceOrder.size())
		mLastDeviceIndex++;

	std::string deviceName = this->mDeviceOrder[mLastDeviceIndex];
	skyMountedDeviceMap::iterator it = mMountedDevices.find(deviceName);

	if(it != mMountedDevices.end())
	{
		return it->second;
	}

	return nullptr;
}

//-----------------------------------------------------------------------------
//  Name : SplitDeviceList (Method)
/// <summary>
/// Splits the device list by ":" and saves them into a vector list. 
/// </summary>
//-----------------------------------------------------------------------------
void skyFileSystem::SplitDeviceList ( std::string list )
{
	skyStringExplode(list, ":", &this->mDeviceOrder);
}