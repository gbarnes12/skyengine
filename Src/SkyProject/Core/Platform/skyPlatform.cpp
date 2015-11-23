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
// Name : skyPlatform.cpp                                                    //
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
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "skyPlatform.h"


///////////////////////////////////////////////////////////////////////////////
// skyPlatform Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : GetTimeNow (Function)
/// <summary>
/// Returns the skyTimeStruct which gets the current time. 
/// This will give you the current date and time at the moment at which you make
/// a call to the function.
/// This is the platform indipendent version.
/// </summary>
//-----------------------------------------------------------------------------
skyTimeStruct skyPlatform::GetTimeNow()
{
	skyTimeStruct tmObject;

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	tmObject = skyWin32Platform::GetTimeNow();
#endif

	return tmObject;
}

//-----------------------------------------------------------------------------
//  Name : IsMemoryAvailable (Function)
/// <summary>
/// Checks whether or not the necessary disk space is available. Use this function
/// in case you want to check if there is still enough memory to make save games 
/// and stuff.
/// This is the platform independent version which takes care of calling the
/// right platform version.
/// </summary>
//-----------------------------------------------------------------------------
bool skyPlatform::IsMemoryAvailable(const DWORDLONG diskSpaceNeeded)
{

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	return skyWin32Platform::IsMemoryAvailable(diskSpaceNeeded);
#endif

	return false;
}


//-----------------------------------------------------------------------------
//  Name : DoesFileExist (Function)
/// <summary>
/// Checks whether or not a specific file exists 
/// </summary>
//-----------------------------------------------------------------------------
bool skyPlatform::DoesFileExist ( std::string path )
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	return skyWin32Platform::DoesFileExist(path);
#endif

	return false;
}

//-----------------------------------------------------------------------------
//  Name : GetFileInfo (Function)
/// <summary>
/// Retrieve new file information
/// </summary>
//-----------------------------------------------------------------------------
skyBool skyPlatform::GetFileInfo ( std::string a_strFilename, sIOFileInfo* a_sInfo )
{
	struct stat stat_buf;
    int rc = stat(a_strFilename.c_str(), &stat_buf);

	a_sInfo->m_i64ATime = stat_buf.st_atime;
	a_sInfo->m_i64CTime = stat_buf.st_ctime;
	a_sInfo->m_i64MTime = stat_buf.st_mtime;
	a_sInfo->m_lSize = stat_buf.st_size;

    return rc == 0 ? true : false;
}

//-----------------------------------------------------------------------------
//  Name : GetTickCount (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
unsigned long skyPlatform::GetCPUTickCount()
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	return skyWin32Platform::GetCPUTickCount();
#endif

	return 0;
}

//-----------------------------------------------------------------------------
//  Name : PerformanceCounter (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatform::PerformanceCounter (unsigned  __int64* save)
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	 skyWin32Platform::PerformanceCounter(save);
#endif
}

//-----------------------------------------------------------------------------
//  Name : PerformanceFrequency (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatform::PerformanceFrequency (unsigned  __int64* save)
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	 skyWin32Platform::PerformanceFrequency(save);
#endif
}


//-----------------------------------------------------------------------------
//  Name : GetExePath (Function)
/// <summary>
///
/// </summary>
//-----------------------------------------------------------------------------
skyWString skyPlatform::GetExePath ()
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	return skyWin32Platform::GetExePath();
#endif

	return L"";
}

//-----------------------------------------------------------------------------
//  Name : CreateCriticalSection (Function)
/// <summary>
/// Creates the correct version of the Critical Selection mutex class. 
/// Use this in order to declare ownership for specific objects e.g. 
/// processes. 
/// </summary>
//-----------------------------------------------------------------------------
skyICriticalSection* skyPlatform::CreateCriticalSection ( void )
{

	skyICriticalSection* pInstance = nullptr;

#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	pInstance = SKY_NEW skyWin32CriticalSection();
#endif
	
	return pInstance;
}

//-----------------------------------------------------------------------------
//  Name : ColorConsole (Function)
/// <summary>
/// Colors the text of the console.
/// </summary>
//-----------------------------------------------------------------------------
void skyPlatform::ColorConsole ( int color )
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	skyWin32Platform::ColorConsole(color);
#endif
}
