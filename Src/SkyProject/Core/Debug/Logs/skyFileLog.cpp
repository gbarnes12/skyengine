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
// Name : skyFileLog.cpp                                                     //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Log file implementation which basically just writes text into a plain    // 
/// text file named "log.txt". Use channel 0 in order to access this log     //
/// file or skyLogChannel::TEXT_FILE.                                        //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//---------------------------------------------------------------------------//

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <fstream> 

///////////////////////////////////////////////////////////////////////////////
// skyFileLog Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyFileLog (Constructor)
/// <summary>
/// Creates the log and takes care of initializing some variables.
/// </summary>
//-----------------------------------------------------------------------------
skyFileLog::skyFileLog ( unsigned int channelID ) 
	: skyILog (channelID)
{
	this->mIsEnabled = true;
	strcpy_s (this->mFileName, "log.txt");

	SKY_PRINT_CONSOLE("skyFileLog", "log system now listens to channel 0 or enum skyLogChannel::TXT_FILE.", 0x0E);

	// Initialize the log file and recreate it if it already exists 
	this->InitializeFile();
}

//-----------------------------------------------------------------------------
//  Name : InitializeFile (Method)
/// <summary>
/// Creates the log and takes care of initializing some variables.
/// </summary>
//-----------------------------------------------------------------------------
void skyFileLog::InitializeFile()
{
	std::ofstream fileStream( this->mFileName );
		
	if( fileStream.is_open() )
	{
		skyTimeStruct now = skyPlatform::GetTimeNow(); // get current date and time

		int month = now.Month + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
		int year = now.Year + 1900; // Year is # years since 1900


		std::string message = "[" + skyToString(now.DayOfMonth) + "." + skyToString(month) + "." + skyToString(year) + ", " + skyToString(now.Hour) + ":" + skyToString(now.Minute) + ":" + skyToString(now.Second) + "][INFO] skyFileLog: log system now listens to channel 0 or enum skyLogChannel::TXT_FILE.";

		fileStream << message << std::endl;
		fileStream.close();
	}
}

//-----------------------------------------------------------------------------
//  Name : skyFileLog (Destructor)
/// <summary>
/// Destructs the object
/// </summary>
//-----------------------------------------------------------------------------
skyFileLog::~skyFileLog ( void )
{
	SKY_PRINT_CONSOLE("skyFileLog", "log system has been destructed now.", 0x0E);
}

//-----------------------------------------------------------------------------
//  Name : VWrite (Method)
/// <summary>
/// Writes a new message to the log file with the current date and time as 
/// wekk as the log level.
/// </summary>
//-----------------------------------------------------------------------------
void skyFileLog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function,  std::string file )
{
	if(this->mIsEnabled)
	{
		std::ofstream fileStream(this->mFileName, std::ios::out | std::ios::app );
		
		if( fileStream.is_open() )
		{
			skyTimeStruct now = skyPlatform::GetTimeNow(); // get current date and time

			int month = now.Month + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
			int year = now.Year + 1900; // Year is # years since 1900


			std::string message = "[" + skyToString(now.DayOfMonth) + "." + skyToString(month) + "." + skyToString(year) + ", " + skyToString(now.Hour) + ":" + skyToString(now.Minute) + ":" + skyToString(now.Second) + "][" + skyLogDispatcher::LogLevelToString(logLevel) + "] " + logMessage;

			fileStream << message << std::endl;
			fileStream.close();
		}
	}
}
	