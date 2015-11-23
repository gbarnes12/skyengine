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
// Name : skyPlatform.h                                                      //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Platform independent wrapper of important functionalities such as        // 
/// CheckFreeDiskSpace or Available Memory etc.                              //
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
//  Name : skyPlatform (Class)
/// <summary>
/// Platform independent wrapper of important functionalities such as 
/// CheckFreeDiskSpace or Available Memory etc. 
/// </summary>
//-----------------------------------------------------------------------------
class skyPlatform 
{
public:

	//-----------------------------------------------------------------------------
	// Public Static Methods
	//-----------------------------------------------------------------------------
	static skyTimeStruct skyPlatform::GetTimeNow();
	static bool skyPlatform::IsMemoryAvailable(const DWORDLONG diskSpaceNeeded);
	static unsigned long skyPlatform::GetCPUTickCount();
	static bool skyPlatform::DoesFileExist ( std::string path );
	static skyICriticalSection* skyPlatform::CreateCriticalSection ( void );
	static void skyPlatform::ColorConsole ( int color );
	static void skyPlatform::PerformanceCounter (unsigned  __int64* save);
	static void skyPlatform::PerformanceFrequency (unsigned  __int64* save);
	static skyWString skyPlatform::GetExePath ();
	static skyBool skyPlatform::GetFileInfo ( std::string a_strFilename, sIOFileInfo* a_sInfo );

	//-----------------------------------------------------------------------------
	//  Name : CreateThread (Function)
	/// <summary>
	/// Creates a new instance of the correct thread implementation. 
	/// </summary>
	//-----------------------------------------------------------------------------
	template<class C, class P>
	static skyIThread<C, P>* CreateThread()
	{
		skyIThread<C, P>* pThread = nullptr;

		#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
		pThread = SKY_NEW skyWin32Thread<skyPlatformFile, skyFileThreadData>();
		#endif

		return pThread;
	}
};