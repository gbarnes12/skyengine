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


skyDiskFileDevice::skyDiskFileDevice ()
	: skyIFileDevice ("disk")
{
}

skyDiskFileDevice::~skyDiskFileDevice ()
{
}

skyIFile* skyDiskFileDevice::VOpen ( std::string filePath, unsigned int fileMode, skyFileSystem* fileSystem )
{
	skyDiskFile* pFile = nullptr;
	skyDiskFile::Spawn ( filePath, fileMode, &pFile);
	return pFile;
}
