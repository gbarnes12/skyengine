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
#include <fstream> 

///////////////////////////////////////////////////////////////////////////////
// skyHTMLLog Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyHTMLLog (Constructor)
/// <summary>
/// Creates the log and takes care of initializing some variables.
/// </summary>
//-----------------------------------------------------------------------------
skyHTMLLog::skyHTMLLog ( unsigned int channelID ) 
	: skyILog (channelID)
{
	this->mIsEnabled = true;
	strcpy_s (this->mFileName, "log.html");

	SKY_PRINT_CONSOLE("skyHTMLLog", "log system now listens to channel 1 or enum skyLogChannel::HTML_FILE.", 0x0E);

	// Initialize the log file and recreate it if it already exists 
	this->InitializeFile();

	this->WriteProcessTitle("Detecting hardware configuration");
	this->WriteSectionTitle("Not implemented yet...");

	// at this point we can start logging errors!
	this->WriteProcessTitle("Logging process started");
	this->StartLogTable(); 
	
	this->VWrite(INFO, "skyHTMLLog: log system now listens to channel 1 or enum skyLogChannel::HTML_FILE.");
}

//-----------------------------------------------------------------------------
//  Name : InitializeFile (Method)
/// <summary>
/// Creates the log and takes care of initializing some variables.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::InitializeFile()
{
	std::ofstream fileStream( this->mFileName );
		
	if( fileStream.is_open() )
	{
		std::string header = "<html>\n";
				header+= "\t<head>\n";
				header+= "\t\t<title>SKY-ENGINE LOG FILE!</title>\n";
				header+= "\t\t<STYLE type='text/css'>\n";
				header+= "\t\t\tbody,td,th {\n\t\t\t\tfont-family: Verdana, Arial, Helvetica, sans-serif;\n\t\t\tfont-size: 9pt;\n\t\t\tcolor: #000000;\n\t\t\t}\n";
				header+= "\t\t\t.app_title {\n\t\t\t\tfont-family: Verdana, Arial, Helvetica, sans-serif;\n\t\t\t\tfont-size: 24pt;\n\t\t\t\tfont-weight: bold;\n\t\t\t\tcolor: #990000;\n\t\t\t\tfont-style: normal;\n\t\t\t}\n";
				header+= "\t\t\t.log_title {\n\t\t\t\tfont-family: Verdana, Arial, Helvetica, sans-serif;\n\t\t\t\tfont-size: 16pt;\n\t\t\t\tfont-weight: bold;\n\t\t\t}\n";
				header+= "\t\t\t.process_title {\n\t\t\t\tfont-size: 12pt;\n\t\t\t\tfont-weight: bold;\n\t\t\t\tborder: 1px solid #999999;\n\t\t\t\tpadding: 2px;\n\t\t\t}\n";
				header+= "\t\t\t.section_title {\n\t\t\t\tfont-size: 10pt;\n\t\t\t\tfont-style: italic;\n\t\t\t\tmargin-left: 10px;\n\t\t\t}\n";
				header+= "\t\t\t.table_style {\n\t\t\t\tmargin-left: 10px;\n\t\t\t\tborder: 1px dotted #999999;\n\t\t\t}\n";
				header+= "\t\t\t.table_head {\n\t\t\t\tfont-weight:bold;\n\t\t\t}\n";
				header+= "\t\t\t.FATAL_ERROR {\n\t\t\t\tcolor:#9e00d2;\n\t\t\t}\n";
				header+= "\t\t\t.CRITICAL_ERROR {\n\t\t\t\tcolor:red;\n\t\t\t}\n";
				header+= "\t\t\t.ASSERT_ERROR {\n\t\t\t\tcolor:#0000ff;\n\t\t\t}\n";
				header+= "\t\t\t.WARNING {\n\t\t\t\tcolor:#ff7e00;\n\t\t\t}\n";
				header+= "\t\t\t.INFO {\n\t\t\t\tcolor:#51c000;\n\t\t\t}\n";
				header+= "\t\t\t.INFO {\n\t\t\t\tcolor:#51c000;\n\t\t\t}\n";
				header+= "\t\t</STYLE>\n";
				header+= "\t</head>\n";
				header+= "<body>\n";
				header+= "\t<div style='width: 100%'>\n";
				header+= "\t\t<div align='justify'>\n";
				header+= "\t\t\t<span class='app_title'>Sky Engine v0.0.1 </span><span class='log_title'>- Information Log</span>\n";
				header+= "\t\t</div>";
				header+= "\t\t<hr/>";
				header+= "<p align='justify'>If you have any problems with this application, please post a copy of this file along with a copy of your dxdiag log file and a detailed description of your problem to the relevant support forum. Please include a list of any relevant hardware or software configurations that may have been reported incorrectly within this debug output in addition to any other information you believe may be in some way related to the fault that occured.</p>";

		fileStream << header;
		fileStream.close();
	}
}

//-----------------------------------------------------------------------------
//  Name : skyFileLog (Destructor)
/// <summary>
/// Destructs the object
/// </summary>
//-----------------------------------------------------------------------------
skyHTMLLog::~skyHTMLLog ( void )
{
	//this->CreateFooter();
	SKY_PRINT_CONSOLE("skyHTMLLog", "log system has been destructed now.", 0x0E);
}

//-----------------------------------------------------------------------------
//  Name : VWrite (Method)
/// <summary>
/// Writes a new message to the log file with the current date and time as 
/// wekk as the log level.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::VWrite ( skyLogLevel logLevel, std::string logMessage, std::string function,  std::string file  )
{
	if(this->mIsEnabled)
	{
		std::ofstream fileStream(this->mFileName, std::ios::out | std::ios::app );
		
		if( fileStream.is_open() )
		{
			skyTimeStruct now = skyPlatform::GetTimeNow(); // get current date and time

			int month = now.Month + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
			int year = now.Year + 1900; // Year is # years since 1900


			std::string table = "\t\t\t<tr>\n";
				table+= "\t\t\t\t<td width='5%' class='"+skyLogDispatcher::LogLevelToString(logLevel)+"'>"+skyLogDispatcher::LogLevelToString(logLevel)+"</td>\n";
				table+= "\t\t\t\t<td width='10%'> " + skyToString(now.DayOfMonth) + "." + skyToString(month) + "." + skyToString(year) + ", " + skyToString(now.Hour) + ":" + skyToString(now.Minute) + ":" + skyToString(now.Second) + "</td>\n";
				table+= "\t\t\t\t<td> "+ logMessage +" </td>\n";
				table+= "\t\t\t</tr>\n";

			fileStream << table;
			fileStream.close();
		}
	}
}


//-----------------------------------------------------------------------------
//  Name : CreateFooter (Function)
/// <summary>
/// Creates the html footer and writes it to the log file.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::CreateFooter()
{
	std::ofstream fileStream( this->mFileName, std::ios::out | std::ios::app );
		
	if( fileStream.is_open() )
	{
		std::string footer = "\t\t</table>\n";
					footer+= "<p class='process_title'>Logging process ended</p>\n";
					footer+= "\t</div>\n";
					footer+= "</body>\n";
					footer+= "</html>";

		fileStream << footer;
		fileStream.close();
	}
}

//-----------------------------------------------------------------------------
//  Name : StartLogTable (Function)
/// <summary>
/// Creates the html code for the table which is the beginning of the logging 
/// session. Once finished it will write the code into the log file.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::StartLogTable()
{

	std::ofstream fileStream( this->mFileName, std::ios::out | std::ios::app );
		
	if( fileStream.is_open() )
	{
		std::string table = "\t\t<table width='98%' border='0' cellpadding='2' cellspacing='0' class='table_style'>\n";
				table+= "\t\t\t<tr>\n";
				table+= "\t\t\t\t<td class='table_head'>Type</td>\n";
				table+= "\t\t\t\t<td class='table_head'>Date / Time</td>\n";
				table+= "\t\t\t\t<td class='table_head'>Description</td>\n";
				table+= "\t\t\t</tr>\n";

		fileStream << table;
		fileStream.close();
	}
}

//-----------------------------------------------------------------------------
//  Name : WriteProcessTitle (Function)
/// <summary>
/// Writes a specific html process title box into the log! This isn't available
/// outside the class.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::WriteProcessTitle(std::string title)
{
	std::ofstream fileStream( this->mFileName, std::ios::out | std::ios::app );
		
	if( fileStream.is_open() )
	{
		std::string html = "<p class='process_title'>" + title + "</p>\n";

		fileStream << html;
		fileStream.close();
	}
}

//-----------------------------------------------------------------------------
//  Name : WriteSectionTitle (Function)
/// <summary>
/// Writes a specific html section title box into the log! This isn't available
/// outside the class.
/// </summary>
//-----------------------------------------------------------------------------
void skyHTMLLog::WriteSectionTitle(std::string title)
{
	std::ofstream fileStream( this->mFileName, std::ios::out | std::ios::app );
		
	if( fileStream.is_open() )
	{
		std::string html = "<p class='section_title'>" + title + "</p>\n";

		fileStream << html;
		fileStream.close();
	}
}
	