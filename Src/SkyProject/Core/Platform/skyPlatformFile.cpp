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
// Name : skyPlatformFile.cpp                                                //
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
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "..\FileSystem\skyAsyncFileOperation.h"
#include "skyPlatformFile.h"


///////////////////////////////////////////////////////////////////////////////
// skyPlatformFile Member Definitions
///////////////////////////////////////////////////////////////////////////////
skyResult skyPlatformFile::Spawn ( std::string path, int mode, bool isAsync, skyPlatformFile** a_pFile)
{
	FILE* pFile = nullptr;


	if( skyPlatform::DoesFileExist ( path ) || SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write) || SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Recreate) )
	{
		std::string stringMode = skyPlatformFile::GetStringFromMode ( mode );
		errno_t error = fopen_s ( &pFile, path.c_str(), stringMode.c_str());
		if( error  )
		{
			 char errorMessage[256];
			 int i = 0;
			 strerror_s(errorMessage, 100, i);
			 SKY_PRINT_CONSOLE("skyPlatformFile:", "couldn't load file at path " + path + " with error message -" + skyToString(errorMessage), 0x0A);
			 return SKY_ERROR;
		}

	}
	else 
	{
		SKY_PRINT_CONSOLE("skyPlatformFile:", "file at path -  " + path + " doesn't exist. ", 0x0A);
		return SKY_ERROR;
	}

	
	*a_pFile = SKY_NEW skyPlatformFile(path, mode, isAsync, pFile);

	return SKY_OK;
}

//-----------------------------------------------------------------------------
//  Name : skyPlatformFile (Constructor)
/// <summary>
/// Opens a stream to a file at a given path. In order to use this file as 
/// an asynchronous file you need to specify it.
/// </summary>
//-----------------------------------------------------------------------------
skyPlatformFile::skyPlatformFile ( std::string path, int mode, bool isAsync, FILE* a_pFile)
{
	this->mPath = path; 
	this->mMode = mode;
	this->mFileMode = GetFileModeFromInt(mode);
	this->mIsAsync = isAsync;
	this->pCriticalSection = nullptr;
	this->pFile = a_pFile;
	
	// once we declared this file as asynchron we need to create a critical section
	if(isAsync)
	{
		this->pCriticalSection = skyPlatform::CreateCriticalSection();
	}
}

//-----------------------------------------------------------------------------
//  Name : skyPlatformFile (Destructor)
/// <summary>
/// Destructs the object and will close the stream.
/// </summary>
//-----------------------------------------------------------------------------
skyPlatformFile::~skyPlatformFile ( void )
{
	if( this->pFile != nullptr )
		fclose ( this->pFile );

	SKY_SAFE_DELETE(this->pCriticalSection);
}

//-----------------------------------------------------------------------------
//  Name : Read (Function)
/// <summary>
/// Reads a specified length of bytes into a given void* buffer.
/// </summary>
//-----------------------------------------------------------------------------
size_t skyPlatformFile::Read ( void* buffer, size_t length )
{
	if(this->mIsAsync)
		this->pCriticalSection->VLock ();

	rewind(this->pFile);

	size_t value = -1;

	if(this->mFileMode == skyFileMode::eFileMode_Ascii)
		value = fread(buffer, sizeof(byte), length, this->pFile);
	else if(this->mFileMode == skyFileMode::eFileMode_Binary)
		value = fread(buffer, sizeof(byte), length, this->pFile);

	if(this->mIsAsync)
		this->pCriticalSection->VUnlock ();

	return value;
}

//-----------------------------------------------------------------------------
//  Name : Write (Function)
/// <summary>
/// Writes a given length of bytes from a void* buffer into a file.
/// </summary>
//-----------------------------------------------------------------------------
size_t skyPlatformFile::Write ( const void* buffer, size_t length)
{
	if(this->mIsAsync)
		this->pCriticalSection->VLock ();

	size_t value = -1;

	if(this->mFileMode == skyFileMode::eFileMode_Ascii)
		value = fwrite(buffer, sizeof(byte), length, this->pFile);
	else if(this->mFileMode == skyFileMode::eFileMode_Binary)
		value = fwrite(buffer, sizeof(byte), length, this->pFile);

	if(this->mIsAsync)
		this->pCriticalSection->VUnlock ();

	return value;
}

//-----------------------------------------------------------------------------
//  Name : Seek (Function)
/// <summary>
/// Sets the position indicator associated with the stream to a new position.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatformFile::Seek ( size_t position )
{
	if(pFile)
	{
		fseek(pFile, position, SEEK_SET);
	}
}

//-----------------------------------------------------------------------------
//  Name : SeekToEnd (Function)
/// <summary>
/// Sets the position indicator associated with the stream to the end of the file.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatformFile::SeekToEnd ( void )
{
	if(pFile)
	{
		fseek (pFile , SEEK_CUR , SEEK_END);
	}
}

//-----------------------------------------------------------------------------
//  Name : Skip (Function)
/// <summary>
/// Not implemented yet!
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatformFile::Skip ( size_t bytes )
{
	SKY_PRINT_CONSOLE("skyPlatformFile", "Skip-Function isn't implemented yet.", 0x0A);
}

//-----------------------------------------------------------------------------
//  Name : Tell (Function)
/// <summary>
/// Returns the current value of the position indicator of the stream.
/// </summary>
//-----------------------------------------------------------------------------
size_t skyPlatformFile::Tell ( void ) const
{
	if(!pFile)
	{
		return -1;
	}

	return ftell ( this->pFile );
}

//-----------------------------------------------------------------------------
//  Name : ReadAsync (Function)
/// <summary>
/// Reads a specific length into a given void buffer in an asynchronous fashion.
/// This will return an AsynchronousFileOperation instance which takes care 
/// of handling all the thread stuff.
/// </summary>
//-----------------------------------------------------------------------------
skySharedAsyncFileOperation skyPlatformFile::ReadAsync ( void* buffer, size_t length )
{
	if(this->mIsAsync)
	{
		skyIThread<skyPlatformFile, skyFileThreadData>* pThread = skyPlatform::CreateThread<skyPlatformFile, skyFileThreadData>();

		skyTransferredBytesData* transferData = SKY_NEW skyTransferredBytesData;
		transferData->mSize = -1;

		skyFileThreadData mData;
		mData.pBuffer = buffer;
		mData.mLength = length;
		mData.pData = transferData;

		pThread->VRun(this, &skyPlatformFile::ReadBufferAsync, mData);

		skySharedAsyncFileOperation pOperation = skySharedAsyncFileOperation(SKY_NEW skyAsyncFileOperation(pThread, transferData));
		return pOperation;
	}

	return skySharedAsyncFileOperation();
}

//-----------------------------------------------------------------------------
//  Name : WriteAsync (Function)
/// <summary>
/// Writes a specific length from a given void buffer to a file in an asynchronous fashion.
/// This will return an AsynchronousFileOperation instance which takes care 
/// of handling all the thread stuff.
/// </summary>
//-----------------------------------------------------------------------------
skySharedAsyncFileOperation skyPlatformFile::WriteAsync ( void* buffer, size_t length )
{
	if(this->mIsAsync)
	{
		skyIThread<skyPlatformFile, skyFileThreadData>* pThread = skyPlatform::CreateThread<skyPlatformFile, skyFileThreadData>();

		skyTransferredBytesData* transferData = SKY_NEW skyTransferredBytesData;
		transferData->mSize = -1;

		skyFileThreadData mData;
		mData.pBuffer = buffer;
		mData.mLength = length;
		mData.pData = transferData;

		pThread->VRun(this, &skyPlatformFile::WriteBufferAsync, mData);

		skySharedAsyncFileOperation pOperation = skySharedAsyncFileOperation(SKY_NEW skyAsyncFileOperation(pThread, transferData));
		return pOperation;
	}

	return skySharedAsyncFileOperation();
}

//-----------------------------------------------------------------------------
//  Name : ReadBufferAsync (Function)
/// <summary>
/// Helper function which takes care of calling the Read-Method.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatformFile::ReadBufferAsync(skyFileThreadData data)
{
	size_t transferredSize = this->Read(data.pBuffer, data.mLength);
	data.pData->mSize = transferredSize;
}

//-----------------------------------------------------------------------------
//  Name : WriteBufferAsync (Function)
/// <summary>
/// Helper function which takes care of calling the Write-Method.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatformFile::WriteBufferAsync(skyFileThreadData data)
{
	size_t transferredSize = this->Write(data.pBuffer, data.mLength);
	data.pData->mSize = transferredSize;
}

//-----------------------------------------------------------------------------
//  Name : GetStringFromMode (Function)
/// <summary>
/// Returns the correct file mode from the enum skyFileSystem::Mode. 
/// </summary>
//-----------------------------------------------------------------------------
std::string skyPlatformFile::GetStringFromMode ( int mode )
{
	std::string mMode = "r";

	if(mode)
	{
		mMode = "";

		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read))
		{
			mMode = "r";
			//mFileMode = skyFileMode::eFileMode_Ascii;
		}

		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Ascii))
		{
			mMode = "r";
			//mFileMode = skyFileMode::eFileMode_Ascii;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Binary))
		{
			mMode = "rb";
			//mFileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write))
		{
			mMode += "w";
			//mFileMode = skyFileMode::eFileMode_Ascii;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Binary))
		{
			mMode = "wb";
			//mFileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Recreate))
		{
			mMode = "w+";
			//mFileMode = skyFileMode::eFileMode_Ascii;
		}

		SKY_TODO("Add the rest of the modes");
		
		/*
		if(mode == (skyFileMode::eFileMode_Write | skyFileMode::eFileMode_Recreate | skyFileMode::eFileMode_Binary))
		{
			mMode = "w+b";
			mFileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(mode == (skyFileMode::eFileMode_Write  | skyFileMode::eFileMode_Append) || mode == (skyFileMode::eFileMode_Append))
		{
			mMode = "a";
			mFileMode = skyFileMode::eFileMode_Ascii;
		}

		if(mode == (skyFileMode::eFileMode_Write | skyFileMode::eFileMode_Append | skyFileMode::eFileMode_Binary))
		{
			mMode = "ab";
			mFileMode = skyFileMode::eFileMode_Binary;
		}*/
	}

	return mMode;
}

eFileMode skyPlatformFile::GetFileModeFromInt ( int mode )
{
	eFileMode fileMode = skyFileMode::eFileMode_Ascii;

	if(mode)
	{
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read))
		{
			fileMode = skyFileMode::eFileMode_Ascii;
		}

		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Ascii))
		{
			fileMode = skyFileMode::eFileMode_Ascii;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Read) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Binary))
		{
			fileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write))
		{
			fileMode = skyFileMode::eFileMode_Ascii;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Binary))
		{
			fileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Write) && SKY_HAS_FLAG(mode, skyFileMode::eFileMode_Recreate))
		{
			fileMode = skyFileMode::eFileMode_Ascii;
		}

		SKY_TODO("Add the rest of the modes");
		
		/*
		if(mode == (skyFileMode::eFileMode_Write | skyFileMode::eFileMode_Recreate | skyFileMode::eFileMode_Binary))
		{
			mMode = "w+b";
			mFileMode = skyFileMode::eFileMode_Binary;
		}
		
		if(mode == (skyFileMode::eFileMode_Write  | skyFileMode::eFileMode_Append) || mode == (skyFileMode::eFileMode_Append))
		{
			mMode = "a";
			mFileMode = skyFileMode::eFileMode_Ascii;
		}

		if(mode == (skyFileMode::eFileMode_Write | skyFileMode::eFileMode_Append | skyFileMode::eFileMode_Binary))
		{
			mMode = "ab";
			mFileMode = skyFileMode::eFileMode_Binary;
		}*/
	}

	return fileMode;
}
