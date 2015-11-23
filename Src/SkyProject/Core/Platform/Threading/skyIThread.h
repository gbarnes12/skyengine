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
// Name : skyIThread.h                                                       //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Multi-Platform interface for a thread. In order to provide different     //
/// implementations for different platforms you need to use this basic       //
/// interface.                                                               //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// Currently this template only supports one parameter for the calling      //
/// thread method. We should maybe look for a solution in order to           //
/// support multiple parameters.                                             //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyIThread (Interface)
/// <summary>
/// The Interface need to implement a Run, Terminate, Suspend, Resume and 
/// IsActive method in order to successfully implement a thread. In order
/// to create a thread class from outside the platform dependent code 
/// you need to call skyPlatform::CreateThread<Class, Param>(); 
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
class skyIThread
{
protected:
	//-----------------------------------------------------------------------------
	// Typedefinitions
	//-----------------------------------------------------------------------------
	typedef void (T::*ThreadFunc)(P);

public:
	//-----------------------------------------------------------------------------
	//  Name : skyIThread (Constructor)
	/// <summary>
	/// Creates a new instance of the thread. You can't create an instance of this
	/// abstract class.
	/// </summary>
	//-----------------------------------------------------------------------------
	skyIThread() 
		: pInstance(NULL), pFunction(NULL)
	{ 
	}

	//-----------------------------------------------------------------------------
	//  Name : skyIThread (Destructor)
	/// <summary>
	/// Destruct the object.
	/// </summary>
	//-----------------------------------------------------------------------------
	virtual ~skyIThread() 
	{
		
	}

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual bool VRun ( T* pClass, ThreadFunc pFunction, P param) = 0;
	virtual void VSuspend ( void ) = 0;
	virtual void VResume ( void ) = 0; 
	virtual void VTerminate ( void ) = 0;
	virtual bool VIsActive ( void ) const  = 0; 

protected:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	T* pInstance;
	ThreadFunc pFunction;
	P mParam; 
};
