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
// Name : skyNetworkLog.h                                                    //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Log implementation of a network log file. Whenever you want a more       //
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
#include "..\skyILog.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyNetworkLog (Class)
/// <summary>
/// Implementation of a network file log. This logger will connect via a udp
/// socket to a server (mostly the inhouse skySuite).
/// </summary>
//-----------------------------------------------------------------------------
class skyNetworkLog : public skyILog
{
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyNetworkLog::skyNetworkLog ( unsigned int channelID );
	virtual skyNetworkLog::~skyNetworkLog ( void ) override;

	void skyNetworkLog::Initialize();

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual void skyNetworkLog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function = "",  std::string file = "" );
	virtual bool skyNetworkLog::VIsEnabled() { return mIsEnabled; }
	virtual void skyNetworkLog::VEnable()  { mIsEnabled = true; }
	virtual void skyNetworkLog::VDisable()  { mIsEnabled = false; }
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	bool mIsEnabled;
	skyUDPSocket* m_pSocket;
};
