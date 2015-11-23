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
/// A basic interface which every file needs to inherit from in order to     //
/// work with our file system.                                               //
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
//  Name : skyIFile (Interface)
/// <summary>
/// skyIFile Interface is used in order to provide the functionality needed
/// by every file. Typical examples are DiskFile, ZipFile, NetworkFile and
/// so on. 
/// </summary>
//-----------------------------------------------------------------------------
class skyIFile 
{
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : skyIFile (Constructor)
	/// <summary>
	/// Every file needs to have a specific file path and mode in order to be 
	/// used sucessfully by the file system.
	/// </summary>
	//-----------------------------------------------------------------------------
	skyIFile::skyIFile ( std::string filePath, unsigned int fileMode ) 
	{ 
		this->mPath = filePath;
		this->mMode = fileMode;
	}

	virtual skyIFile::~skyIFile ( ) { }

	//-------------------------------------------------------------------------
    // Virtual Public Methods
    //-------------------------------------------------------------------------
	virtual size_t skyIFile::VRead ( void* buffer, size_t length ) = 0;
	virtual size_t skyIFile::VWrite ( void* buffer, size_t length ) = 0;
	virtual size_t skyIFile::VGetTotalSize ( void ) = 0;
protected:
	//-------------------------------------------------------------------------
    // Protected Members
    //-------------------------------------------------------------------------
	std::string mPath;
	unsigned int mMode;
};