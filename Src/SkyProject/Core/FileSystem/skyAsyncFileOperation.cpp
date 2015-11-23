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
// Name : skyAsyncFileOperation.cpp                                          //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// This operation can be used to control the asynchron read and write       //
/// procedures for the skyPlatformFile. You can cancel the operation or      //
/// wait till its finished.                                                  //
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
#include "skyAsyncFileOperation.h"

///////////////////////////////////////////////////////////////////////////////
// skyEventDispatcher Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyAsyncFileOperation (Constructor)
/// <summary>
/// Creates a new asynchronous file operation with a given thread you need 
/// to supply a pointer to a skyTransferredBytesData struct in order to 
/// retrieve the read or write bytes at the end of the operation.
/// </summary>
//-----------------------------------------------------------------------------
skyAsyncFileOperation::skyAsyncFileOperation(skyPlatformFileThread pThread, skyTransferredBytesData* size)
{
	if(this->pThread)
		this->pThread = pThread;
	else
		this->pThread = nullptr;
	
	if(size)
		this->pSize = size;

	SKY_PRINT_CONSOLE("skyAsyncFileOperation", "file operation started!", 0x0B);
}

//-----------------------------------------------------------------------------
//  Name : skyAsyncFileOperation (Destructor)
/// <summary>
/// Destructs the object. If the thread isn't finished yet it will wait 
/// until its finished and after that deletes the thread.
/// </summary>
//-----------------------------------------------------------------------------
skyAsyncFileOperation::~skyAsyncFileOperation(void)
{
	if( this->pThread )
	{
		if( !this->IsFinished () )
			this->WaitUntilFinished ();

		SKY_SAFE_DELETE(this->pSize);
		SKY_SAFE_DELETE(this->pThread);
	}
}

//-----------------------------------------------------------------------------
//  Name : IsFinished (Method)
/// <summary>
/// Checks whether or not the thread is still active or not.
/// </summary>
//-----------------------------------------------------------------------------
bool skyAsyncFileOperation::IsFinished ( void ) const
{
	if( !this->pThread )
		return true;

	return this->pThread->VIsActive();
}

//-----------------------------------------------------------------------------
//  Name : WaitUntilFinished (Method)
/// <summary>
/// Waits till the thread is finished. Returns the processed bytes or -1 if 
/// anything was wrong. 
/// </summary>
//-----------------------------------------------------------------------------
size_t skyAsyncFileOperation::WaitUntilFinished ( void ) const
{
	size_t mSize = -1;

	if( !this->pThread )
		return mSize;
	
	// wait as long as the thread is still active!
	while (this->pThread->VIsActive());

	SKY_PRINT_CONSOLE("skyAsyncFileOperation", "file operation finished!", 0x0B);

	if(this->pSize)
		mSize = this->pSize->mSize;

	return mSize;
}

//-----------------------------------------------------------------------------
//  Name : Cancel (Method)
/// <summary>
/// Cancels the thread.
/// </summary>
//-----------------------------------------------------------------------------
void skyAsyncFileOperation::Cancel ( void )
{
	if(this->pThread)
		this->pThread->VTerminate ();
}