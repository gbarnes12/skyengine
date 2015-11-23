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
// Name : skyPlatformFile.h                                                  //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Platform independent implementation of a hard drive file. This class     //
/// provides asynchronous methods, too.                                      //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //


//-----------------------------------------------------------------------------
// Structs 
//-----------------------------------------------------------------------------
struct skyTransferredBytesData
{
	size_t mSize;
};

struct skyFileThreadData
{
	void* pBuffer;
	size_t mLength;
	skyTransferredBytesData* pData;
};

//-----------------------------------------------------------------------------
// Type definitions and forward declarations. 
//-----------------------------------------------------------------------------
class skyAsyncFileOperation;
typedef shared_ptr<skyAsyncFileOperation> skySharedAsyncFileOperation;

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyPlatformFile (Class)
/// <summary>
/// Platform independent class for a file. This class provides both asynchronous
/// and synchronous read and write operations for files. Furthermore files can
/// be used in binary or ascii mode.
/// </summary>
//-----------------------------------------------------------------------------
class skyPlatformFile 
{
public:
	static skyResult skyPlatformFile::Spawn ( std::string path, int mode, bool isAsync, skyPlatformFile** a_pFile);
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyPlatformFile::~skyPlatformFile ( void );


	//-------------------------------------------------------------------------
    // Synchronous Methods
    //-------------------------------------------------------------------------
	size_t skyPlatformFile::Read ( void* buffer, size_t length );
	size_t skyPlatformFile::Write ( const void* buffer, size_t length);

	//-------------------------------------------------------------------------
    // Asynchronous Methods
    //-------------------------------------------------------------------------
	skySharedAsyncFileOperation skyPlatformFile::ReadAsync ( void* buffer, size_t length );
	skySharedAsyncFileOperation skyPlatformFile::WriteAsync ( void* buffer, size_t length );

	//-------------------------------------------------------------------------
    // Public Mehtods
    //-------------------------------------------------------------------------
	void skyPlatformFile::Seek ( size_t position );
	void skyPlatformFile::SeekToEnd ( void );
	void skyPlatformFile::Skip ( size_t bytes );
	size_t skyPlatformFile::Tell ( void ) const; 

	//-------------------------------------------------------------------------
    // Public Static Mehtods
    //-------------------------------------------------------------------------
	static std::string skyPlatformFile::GetStringFromMode ( int mode );

private:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyPlatformFile::skyPlatformFile ( std::string path, int mode, bool isAsync, FILE* a_pFile);

	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	std::string mPath; 
	int mMode;
	bool mIsAsync;
	skyFileMode mFileMode;
	FILE* pFile;
	skyICriticalSection* pCriticalSection;

	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	eFileMode skyPlatformFile::GetFileModeFromInt ( int mode );
	void skyPlatformFile::ReadBufferAsync(skyFileThreadData data);
	void skyPlatformFile::WriteBufferAsync(skyFileThreadData data);
};

//-------------------------------------------------------------------------
// Typedefinitions
//-------------------------------------------------------------------------
typedef skyIThread<skyPlatformFile, skyFileThreadData>* skyPlatformFileThread;