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
#include "skyDiskFile.h"

skyResult skyDiskFile::Spawn ( std::string filePath, unsigned int fileMode, skyDiskFile** a_pFile )
{
	skyPlatformFile* a_pPFile = nullptr;
	skyResult hr;
	SKY_VR(skyPlatformFile::Spawn ( filePath, fileMode, false, &a_pPFile ));
	*a_pFile = SKY_NEW skyDiskFile(filePath, fileMode, a_pPFile);

	return SKY_OK;
}

skyDiskFile::skyDiskFile (  std::string filePath, unsigned int fileMode, skyPlatformFile* a_pFile )
	: skyIFile (filePath, fileMode)
	, pFile(a_pFile)
{
	
}

skyDiskFile::~skyDiskFile ( )
{
	SKY_SAFE_DELETE ( this->pFile );
}


size_t skyDiskFile::VRead ( void* buffer, size_t length )
{
	return this->pFile->Read ( buffer, length );
}

size_t skyDiskFile::VWrite ( void* buffer, size_t length )
{
	return this->pFile->Write ( buffer, length );
}

size_t skyDiskFile::VGetTotalSize ( void )
{
	this->pFile->SeekToEnd();

	return this->pFile->Tell();
}