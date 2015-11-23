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


class skyDiskFile : public skyIFile 
{
public:
	static skyResult skyDiskFile::Spawn ( std::string filePath, unsigned int fileMode, skyDiskFile** a_pFile );
	virtual skyDiskFile::~skyDiskFile ( );


	virtual size_t skyDiskFile::VRead ( void* buffer, size_t length );
	virtual size_t skyDiskFile::VWrite ( void* buffer, size_t length );
	virtual size_t skyDiskFile::VGetTotalSize ( void );
private:
	skyPlatformFile* pFile;

	skyDiskFile::skyDiskFile ( std::string filePath, unsigned int fileMode, skyPlatformFile* a_pFile );
};