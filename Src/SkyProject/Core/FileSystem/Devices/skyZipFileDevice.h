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


class skyZipFileDevice : public skyIFileDevice 
{
public:
	skyZipFileDevice::skyZipFileDevice ();
	virtual skyZipFileDevice::~skyZipFileDevice ();

	virtual skyIFile* skyZipFileDevice::VOpen (std::string filePath, unsigned int fileMode, skyFileSystem* fileSystem = nullptr);
};