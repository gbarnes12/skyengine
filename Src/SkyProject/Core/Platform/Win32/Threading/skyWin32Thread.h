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
// Name : skyWin32Thread.h                                                   //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Win32 Thread implementation. This class is used in order to create       //
/// new threads. It can be run by starting VRun. You need to supply          //
/// an valid instance to the class method you want to start and the method.  //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// Implement variadic parameters thus we can have as much parameters        //
/// to the given method as we want.                                          //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)

//-----------------------------------------------------------------------------
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyWin32Thread (Class)
/// <summary>
/// Basic interface that provides necessary implementation details for       
/// any platform view within the project. Basically it is used to          
/// create windows for linux, windows or mac os which we can render to
/// at specific point.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
class skyWin32Thread : public skyIThread<T, P>
{
	
public:

	//-----------------------------------------------------------------------------
	//  Name : skyWin32Thread (Constructor)
	/// <summary>
	/// Creates a new instance of the windows 32 thread implementation.
	/// </summary>
	//-----------------------------------------------------------------------------
	skyWin32Thread() 
		: skyIThread<T, P>()
	{
		this->mThread = NULL; 
		this->mThreadID = (DWORD)-1;
	}

	//-----------------------------------------------------------------------------
	//  Name : skyWin32Thread (Destructor)
	/// <summary>
	/// Destructs the object if the object is still active it can't bet terminated
	/// </summary>
	//-----------------------------------------------------------------------------
	virtual ~skyWin32Thread() 
	{ 
		if(this->VIsActive ())
			this->VTerminate ();
	}

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual bool VRun ( T* pClass, ThreadFunc pFunction, P param) override;
	virtual void VSuspend ( void )  override;
	virtual void VResume ( void )  override; 
	virtual void VTerminate ( void )  override;
	virtual bool VIsActive ( void ) const  override; 

protected:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	HANDLE mThread;
	DWORD mThreadID;

	//-------------------------------------------------------------------------
    // Static Private Members
    //-------------------------------------------------------------------------
	static DWORD WINAPI StartThread( void* pParam );
};

//-----------------------------------------------------------------------------
//  Name : VRun (Method)
/// <summary>
/// Starts the thread with the supplied threading function. 
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
bool skyWin32Thread<T, P>::VRun ( T* pClass, ThreadFunc pFunction, P param)
{
	this->pInstance = pClass; 
	this->pFunction = pFunction; 
	this->mParam = param;

	this->mThread = CreateThread( NULL, 0, skyWin32Thread<T, P>::StartThread, this, 0, &mThreadID );
	
	return (this->mThread != NULL);
}

//-----------------------------------------------------------------------------
//  Name : VSuspend (Method)
/// <summary>
/// Suspends the given thread.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
void skyWin32Thread<T, P>::VSuspend ( void )
{
	if(this->mThread)
		::SuspendThread(this->mThread);
}

//-----------------------------------------------------------------------------
//  Name : VResume (Method)
/// <summary>
/// Resumes the thread again.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
void skyWin32Thread<T, P>::VResume ( void )
{
	if(this->mThread)
	{
		int resumeCount = ::ResumeThread( this->mThread );
		while (resumeCount > 1)
			resumeCount = ::ResumeThread( this->mThread );
	}
}

//-----------------------------------------------------------------------------
//  Name : VTerminate (Method)
/// <summary>
/// Terminates the thread and will close the handle.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
void skyWin32Thread<T, P>::VTerminate ( void )
{
	if(this->mThread)
	{
		::TerminateThread(this->mThread, 0 );
		::CloseHandle ( this->mThread );
		this->mThread = NULL;
	}
}

//-----------------------------------------------------------------------------
//  Name : VIsActive (Method)
/// <summary>
/// Checks whether or not the thread is still active or not.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
bool skyWin32Thread<T, P>::VIsActive ( void ) const
{
	return ((this->mThread != NULL) && (::WaitForSingleObject(this->mThread, 0) != WAIT_OBJECT_0));
}

//-----------------------------------------------------------------------------
//  Name : StartThread (Method)
/// <summary>
/// Static helper function in order to succesffully start the supplied class 
/// method on the instance.
/// </summary>
//-----------------------------------------------------------------------------
template<class T, class P>
DWORD WINAPI skyWin32Thread<T, P>::StartThread( void* pParam )
{
	skyWin32Thread* pInstance = reinterpret_cast<skyWin32Thread*> ( pParam ); 

	if( !pInstance ) 
		return (DWORD) - 1; 

	T* pClassInstance = pInstance->pInstance;
	ThreadFunc pfFunc = pInstance->pFunction;
    P param = pInstance->mParam;

	((*pClassInstance).*pfFunc)( param );

	return 0;
}
#endif