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
// Name : skyWin32CriticalSection.h                                          //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// In concurrent programming, a critical section is a piece of code that    // 
/// accesses a shared resource (data structure or device) that must not be   // 
/// concurrently accessed by more than one thread of execution.              //
/// A critical section will usually terminate in fixed time, and a thread,   //
/// task, or process will have to wait a fixed time to enter it              //
/// (aka bounded waiting). Some synchronization mechanism is required at the //
/// entry and exit of the critical section to ensure exclusive use, for      //
/// example a semaphore. Source: Wikipedia.                                  //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //


//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyWin32CriticalSection (Interface)
/// <summary>
/// Win32 implementation of a critical section. This is used in order to control
/// concurrent access to globally used resources!
/// </summary>
//-----------------------------------------------------------------------------
class skyWin32CriticalSection : public skyICriticalSection
{
public:
	//-----------------------------------------------------------------------------
	//  Name : skyWin32CriticalSection (Constructor)
	/// <summary>
	/// Creates a new instance of the windows 32 critical section implementation
	/// and initializes it.
	/// </summary>
	//-----------------------------------------------------------------------------
	skyWin32CriticalSection::skyWin32CriticalSection ( void ) 
	{ 
		InitializeCriticalSection( &mCS );
	}

	//-----------------------------------------------------------------------------
	//  Name : skyWin32Thread (Destructor)
	/// <summary>
	/// Deletes the critical section again.
	/// </summary>
	//-----------------------------------------------------------------------------
	virtual skyWin32CriticalSection::~skyWin32CriticalSection ( void ) 
	{ 
		DeleteCriticalSection ( &mCS );
	}

	//-----------------------------------------------------------------------------
	//  Name : VLock (Constructor)
	/// <summary>
	/// Will lock the current section to the thread calling this method!
	/// </summary>
	//-----------------------------------------------------------------------------
	virtual void skyWin32CriticalSection::VLock ( void ) 
	{
		EnterCriticalSection ( &mCS );
	}

	//-----------------------------------------------------------------------------
	//  Name : VUnlock (Constructor)
	/// <summary>
	/// Will unlock the current section to the thread calling this method!
	/// </summary>
	//-----------------------------------------------------------------------------
	virtual void skyWin32CriticalSection::VUnlock ( void )
	{
		LeaveCriticalSection ( &mCS );
	}
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	mutable CRITICAL_SECTION mCS;
};