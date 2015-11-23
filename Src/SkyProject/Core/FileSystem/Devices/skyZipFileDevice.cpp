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
// Name : skyIFile.h                                                         //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// 
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
#include "skyZipFileDevice.h"


skyZipFileDevice::skyZipFileDevice ()
	: skyIFileDevice ("zip")
{
}

skyZipFileDevice::~skyZipFileDevice ()
{
}

skyIFile* skyZipFileDevice::VOpen ( std::string filePath, unsigned int fileMode, skyFileSystem* fileSystem )
{
	skyIFileDevice* pDevice = fileSystem->GetNextDevice();
	if(pDevice)
	{
		return pDevice->VOpen(filePath, fileMode, fileSystem);
	}

	return nullptr;
}
