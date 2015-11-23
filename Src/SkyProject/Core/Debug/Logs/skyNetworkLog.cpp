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
// Name : skyHTMLLog.cpp                                                     //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Log implementation of a html log file. Whenever you want a more          //
/// formatted result write to this log channel instead of the txt channel.   //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// Still needs hardware detection capabilities and some css color values    //
/// need to be adjusted in order to fit the log levels.                      //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//---------------------------------------------------------------------------//

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyNetworkLog.h"

///////////////////////////////////////////////////////////////////////////////
// skyHTMLLog Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyHTMLLog (Constructor)
/// <summary>
/// Creates the log and takes care of initializing some variables.
/// </summary>
//-----------------------------------------------------------------------------
skyNetworkLog::skyNetworkLog ( unsigned int channelID ) 
	: skyILog (channelID)
{
	this->mIsEnabled = false;
	this->m_pSocket = SKY_NULL;

	

	SKY_PRINT_CONSOLE("skyNetworkLog", "log system now listens to channel 3 or enum skyLogChannel::NETWORK.", 0x0E);
}


//-----------------------------------------------------------------------------
//  Name : skyFileLog (Destructor)
/// <summary>
/// Destructs the object
/// </summary>
//-----------------------------------------------------------------------------
skyNetworkLog::~skyNetworkLog ( void )
{
	SKY_PRINT_CONSOLE("skyNetworkLog", "log system has been destructed now.", 0x0E);
	this->mIsEnabled = false;
	SKY_SAFE_DELETE(m_pSocket);
}

//-----------------------------------------------------------------------------
//  Name : skyFileLog (Destructor)
/// <summary>
/// Destructs the object
/// </summary>
//-----------------------------------------------------------------------------
void skyNetworkLog::Initialize()
{
	skyResult hr;
	SKY_V(skyUDPSocket::Spawn(&this->m_pSocket));

	SKY_V(m_pSocket->Connect("127.0.0.1", 1389)); 
	
	SKY_PRINT_CONSOLE("skyNetworkLog", "Attempting to connect to socket at address 127.0.0.1", 0x0E);
	if(hr == SKY_OK) {
		this->mIsEnabled = true;
		SKY_PRINT_CONSOLE("skyNetworkLog", "Successfully connected to 127.0.0.1", 0x0E);
	}
	else 
		SKY_PRINT_CONSOLE("skyNetworkLog", "Failed to connect to 127.0.0.1", 0x0E);
}


//-----------------------------------------------------------------------------
//  Name : VWrite (Method)
/// <summary>
/// Writes a new message to the log file with the current date and time as 
/// wekk as the log level.
/// </summary>
//-----------------------------------------------------------------------------
void skyNetworkLog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function, std::string file  )
{
	if(!m_pSocket)
		return;

	if(this->mIsEnabled)
	{
		m_pSocket->Send("log;" + skyLogDispatcher::LogLevelToString(logLevel) + ";" + function + ";" + logMessage + ";" + file);
	}
}

	