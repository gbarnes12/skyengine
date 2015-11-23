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
// Name : skyAsyncFileOperation.h                                            //
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
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyAsyncFileOperation (Interface)
/// <summary>
/// An asynchron file operation will be returned from the skyPlatformFile 
/// whenever one calls AsyncRead or AsyncWrite. This class takes care of 
/// cleaning up the thread class and so on.
/// </summary>
//-----------------------------------------------------------------------------
class skyAsyncFileOperation 
{
public:
	//-----------------------------------------------------------------------------
	// Constructor & Destructor
	//-----------------------------------------------------------------------------
	skyAsyncFileOperation(skyPlatformFileThread pThread, skyTransferredBytesData* size);
	~skyAsyncFileOperation(void);

	//-----------------------------------------------------------------------------
	// Public Methods
	//-----------------------------------------------------------------------------
	bool IsFinished ( void ) const;
	size_t WaitUntilFinished ( void ) const;
	void Cancel ( void );

private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	skyPlatformFileThread pThread;
	skyTransferredBytesData* pSize;
};