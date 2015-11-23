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
// Name : skyILog.h                                                          //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Interface which every log class needs to inherit from. You need to       //
/// provide your own functionality for the Log methods.                      //
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
//#include "skyLogDispatcher.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyILog (Class)
/// <summary>
/// Interface which every log class needs to inherit from. You need to   
/// provide your own functionality for the Log methods.
/// </summary>
//-----------------------------------------------------------------------------
class skyILog
{
public:
	//-------------------------------------------------------------------------
    // Public Constructor & Destructor
    //-------------------------------------------------------------------------
	skyILog::skyILog (unsigned int channelID) 
	{ 
		this->mChannelId = channelID;
		this->AddToList (); 
	}

	virtual skyILog::~skyILog(void) {}


	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual void skyILog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function = "",  std::string file = "" ) = 0;
	virtual bool skyILog::VIsEnabled() = 0;
	virtual void skyILog::VEnable() = 0;
	virtual void skyILog::VDisable() = 0;

	static skyILog* skyILog::FindLog ( unsigned int channelID );

private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	skyILog* pNext;
	unsigned int mChannelId;

	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	void skyILog::AddToList ( void );
};

static skyILog* pLogListHead = nullptr;
static skyILog* pLogListTail = nullptr;