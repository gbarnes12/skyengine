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
// Name : skyFileLog.h                                                       //
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

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyFileLog (Class)
/// <summary>
/// Implementation of a text file log. This logger will write to log.txt 
/// and uses 0 as channel id.
/// </summary>
//-----------------------------------------------------------------------------
class skyFileLog : public skyILog
{
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyFileLog::skyFileLog ( unsigned int channelID );
	virtual skyFileLog::~skyFileLog ( void ) override;

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual void skyFileLog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function = "",  std::string file = "" );
	virtual bool skyFileLog::VIsEnabled() { return mIsEnabled; }
	virtual void skyFileLog::VEnable()  { mIsEnabled = true; }
	virtual void skyFileLog::VDisable()  { mIsEnabled = false; }
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	bool mIsEnabled;
	char mFileName[8];

	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	void skyFileLog::InitializeFile();
};
