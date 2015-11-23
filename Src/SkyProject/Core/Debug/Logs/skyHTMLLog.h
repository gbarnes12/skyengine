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
// Name : skyHTMLLog.h                                                       //
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

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyHTMLLog (Class)
/// <summary>
/// Implementation of a html file log. This logger will write to log.html 
/// and uses 1 as channel id.
/// </summary>
//-----------------------------------------------------------------------------
class skyHTMLLog : public skyILog
{
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyHTMLLog::skyHTMLLog ( unsigned int channelID );
	virtual skyHTMLLog::~skyHTMLLog ( void ) override;

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual void skyHTMLLog::VWrite ( skyLogLevel logLevel, std::string logMessage , std::string function = "",  std::string file = "" );
	virtual bool skyHTMLLog::VIsEnabled() { return mIsEnabled; }
	virtual void skyHTMLLog::VEnable()  { mIsEnabled = true; }
	virtual void skyHTMLLog::VDisable()  { mIsEnabled = false; }
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	bool mIsEnabled;
	char mFileName[9];

	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	void skyHTMLLog::StartLogTable();
	void skyHTMLLog::CreateFooter();
	void skyHTMLLog::WriteProcessTitle(std::string title);
	void skyHTMLLog::WriteSectionTitle(std::string title);
	void skyHTMLLog::InitializeFile();
};
