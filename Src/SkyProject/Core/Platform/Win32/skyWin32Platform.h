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

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)


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
class skyWin32Platform 
{
	friend class skyPlatform;
private:

	//-----------------------------------------------------------------------------
	// Private Static Methods
	//-----------------------------------------------------------------------------
	static skyTimeStruct skyWin32Platform::GetTimeNow();
	static bool skyWin32Platform::IsMemoryAvailable(const DWORDLONG diskSpaceNeeded);
	static unsigned long skyWin32Platform::GetCPUTickCount();
	static bool skyWin32Platform::DoesFileExist ( std::string path );
	static void skyWin32Platform::ColorConsole ( int color );
	static void skyWin32Platform::PerformanceCounter (unsigned __int64* save);
	static void skyWin32Platform::PerformanceFrequency (unsigned  __int64* save);
	static skyWString skyWin32Platform::GetExePath ();
};
#endif
