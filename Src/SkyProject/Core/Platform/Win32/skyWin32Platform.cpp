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
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
#include <fstream>
#include <direct.h>

//-----------------------------------------------------------------------------
//  Name : GetTimeNow (Function)
/// <summary>
/// Returns the skyTimeStruct which gets the current time. 
/// This will give you the current date and time at the moment at which you make
/// a call to the function. If anything goes wrong this function will return 
/// an empty struct with 0 values. Furthermore it will print a specific debug 
/// message. 
/// For more see http://msdn.microsoft.com/en-us/library/a442x3ye(v=vs.80).aspx
/// </summary>
//-----------------------------------------------------------------------------
skyTimeStruct skyWin32Platform::GetTimeNow()
{
	__time64_t long_time; // stores the timestamp of the current time ... as a 64 bit long type
	tm now; // will store the data which is needed to get the date and time
	
	_time64 ( &long_time );  // save time into the time64 long datatype 

	errno_t error;
    error = _localtime64_s ( &now, &long_time ); // now convert the long to a specific struct format.

	// if anything is wrong we return a empty time struct. 
	// and print a message to the console.
	if(error)
	{
		SKY_PRINT_CONSOLE("skyWin32Platform", "Error while calling GetTimeNow - Invalid argument to _localtime64_s.", 0x0C);
		SKY_WARNING(0, "skyWin32Platform: Error while calling GetTimeNow - Invalid argument to _localtime64_s.");

		return skyTimeStruct();
	}

	skyTimeStruct timeStruct;

	timeStruct.Hour = now.tm_hour;
	timeStruct.ISDST = now.tm_isdst;
	timeStruct.DayOfMonth = now.tm_mday;
	timeStruct.Minute = now.tm_min;
	timeStruct.Month = now.tm_mon;
	timeStruct.Second = now.tm_sec;
	timeStruct.DayOfYear = now.tm_yday;
	timeStruct.DayOfWeek = now.tm_wday;
	timeStruct.Year = now.tm_year;

	return timeStruct;
};

//-----------------------------------------------------------------------------
//  Name : PerformanceCounter (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
void skyWin32Platform::PerformanceFrequency (unsigned  __int64* save)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)save);
}


//-----------------------------------------------------------------------------
//  Name : PerformanceCounter (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
void skyWin32Platform::PerformanceCounter (unsigned __int64* save)
{
	QueryPerformanceCounter((LARGE_INTEGER*)save);
}

//-----------------------------------------------------------------------------
//  Name : GetExePath (Function)
/// <summary>
///
/// </summary>
//-----------------------------------------------------------------------------
skyWString skyWin32Platform::GetExePath ()
{   
	skyWideChar wstrPath[MAX_PATH]; 
	skyWString strPath;
	HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
		 // When passing NULL to GetModuleHandle, it returns handle of exe itself
		GetModuleFileName(hModule, wstrPath, (sizeof(wstrPath))); 
	}
	strPath = wstrPath;
	return strPath;
}

//-----------------------------------------------------------------------------
//  Name : GetCPUTickCount (Function)
/// <summary>
/// Returns the current tick count of the cpu processor.
/// </summary>
//-----------------------------------------------------------------------------
unsigned long skyWin32Platform::GetCPUTickCount()
{
	return GetTickCount();
}

//-----------------------------------------------------------------------------
//  Name : DoesFileExist (Function)
/// <summary>
/// Checks whether or not a specific file exists 
/// </summary>
//-----------------------------------------------------------------------------
bool skyWin32Platform::DoesFileExist ( std::string path )
{
	FILE* fp;

	errno_t error = fopen_s(&fp, path.c_str(), "r");

	if( !error ) 
	{
		fclose(fp);
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//  Name : IsMemoryAvailable (Function)
/// <summary>
/// Checks whether or not the necessary disk space is available. Use this function
/// in case you want to check if there is still enough memory to make save games 
/// and stuff.
/// This function is taken from Game Coding Complete.
/// </summary>
//-----------------------------------------------------------------------------
 bool skyWin32Platform::IsMemoryAvailable(const DWORDLONG diskSpaceNeeded)
 {
	 // Check for enough free disk space on the current disk.
    int const drive = _getdrive();
    struct _diskfree_t diskfree;

    errno_t error;
	error = _getdiskfree(drive, &diskfree);

	if(error)
	{
		SKY_PRINT_CONSOLE("skyWin32Platform:", "Error while calling IsMemoryAvailable - Invalid argument to _getdiskfree.", 0x0C);
		SKY_WARNING(0, "skyWin32Platform: Error while calling IsMemoryAvailable - Invalid argument to _getdiskfree.");

		return false;
	}

    unsigned __int64 const neededClusters = 
            diskSpaceNeeded /(diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

    if (diskfree.avail_clusters < neededClusters)
    {
		return false;
    }

    return true;
 }

 //-----------------------------------------------------------------------------
//  Name : ColorConsole (Function)
/// <summary>
/// Colors the text of the console.
/// </summary>
//-----------------------------------------------------------------------------
void skyWin32Platform::ColorConsole ( int color )
{
#if  defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
	HANDLE mHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(mHandle, color);
#endif
}
#endif