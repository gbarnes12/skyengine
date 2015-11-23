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
// Name : skyICriticalSection.h                                              //
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
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyICriticalSection (Interface)
/// <summary>
/// Basic interface implementation of a platform independent critical section.
/// You still need to implement all the platforms yourself of course in order
/// to support new platforms. But this is the interface that is used by 
/// all the platform independent code in the engine. 
/// </summary>
//-----------------------------------------------------------------------------
class skyICriticalSection
{
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyICriticalSection::skyICriticalSection ( void ) { };
	virtual skyICriticalSection::~skyICriticalSection ( void ) { }

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual void skyICriticalSection::VLock ( void ) = 0;
	virtual void skyICriticalSection::VUnlock ( void ) = 0;
};