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
// Name : skyLogDispatcher.cpp                                               //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Wrapper functionality in order to successfully dispatch log messages     //
/// to the corresponding log channels.                                       //
/// Logging classes have been fully switched to single classes instea of     //
/// one singleton in order to provide more than one log channel and          //
/// thus we can declare multiple log classes such as NetworkLog, ConsoleLog, //
/// FileLog and so on.                                                       //
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
#include "skyLogDispatcher.h"
#include "skyILog.h"


///////////////////////////////////////////////////////////////////////////////
// skyLogDispatcher Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : Write (Method)
/// <summary>
/// Writes a specific message to a specific log channel and a log level. 
/// This method checks whether or not the channel is active and enabled, too.
/// </summary>
//-----------------------------------------------------------------------------
void skyLogDispatcher::Write (unsigned int logChannel, skyLogLevel logLevel, std::string logMessage )
{
	skyILog* log = skyILog::FindLog(logChannel);
	if(log) 
	{
		// whenever the channel exist we can call the write method on it if the object is enabled!
		if(log->VIsEnabled())
			log->VWrite(logLevel, logMessage);
	}
	else
	{
		SKY_PRINT_CONSOLE("skyLogDispatcher", skyToString("Log Channel:") + skyToString(logChannel) + skyToString(" doesn't exist in log list."), 0x0E);
	}
}

//-----------------------------------------------------------------------------
//  Name : Enable (Method)
/// <summary>
/// Enables a specific log channel thus it can be used and will be written to.
/// </summary>
//-----------------------------------------------------------------------------
void skyLogDispatcher::Enable (unsigned int logChannel)
{
	skyILog* log = skyILog::FindLog(logChannel);
	if(log) 
		log->VEnable();
	else
		SKY_PRINT_CONSOLE("skyLogDispatcher", skyToString("Log Channel:") + skyToString(logChannel) + skyToString(" doesn't exist in log list."), 0x0E);
}

//-----------------------------------------------------------------------------
//  Name : Disable (Method)
/// <summary>
/// Disables a specific log channel thus it won't log any more events!
/// </summary>
//-----------------------------------------------------------------------------
void skyLogDispatcher::Disable (unsigned int logChannel)
{
	skyILog* log = skyILog::FindLog(logChannel);
	if(log) 
		log->VDisable();
	else
		SKY_PRINT_CONSOLE("skyLogDispatcher", skyToString("Log Channel:") + skyToString(logChannel) + skyToString(" doesn't exist in log list."), 0x0E);
}

//-----------------------------------------------------------------------------
//  Name : LogLevelToString (Method)
/// <summary>
/// Converts the provided log level into a string and returns it.
/// </summary>
//-----------------------------------------------------------------------------
std::string skyLogDispatcher::LogLevelToString ( skyLogLevel logLevel )
{
	std::string type = "UNKNOWN";
	
	switch( logLevel )
	{
		case FATAL_ERROR:
			type = "FATAL_ERROR";
		break;
		case CRITICAL_ERROR:
			type = "CRITICAL_ERROR";
		break;
		case ASSERT_ERROR:
			type = "ASSERT_ERROR";
		break;
		case WARNING:
			type = "WARNING";
		break;
		case INFO:
			type = "INFO";
		break;
		case MEMORY_ALLOCATION:
			type = "MEMORY_ALLOCATION";
		break;
		case MEMORY_DELETION:
			type = "MEMORY_DELETION";
		break;
	}


	return type;
}