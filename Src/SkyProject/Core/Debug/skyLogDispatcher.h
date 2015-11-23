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
// Name : skyLogDispatcher.h                                                 //
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

//-----------------------------------------------------------------------------
// TypeDefs
//-----------------------------------------------------------------------------
class skyILog;

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
#if !defined(SKY_BUILD_MASTER)
#define SKY_FATAL_ERROR(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::FATAL_ERROR, msg);
#define SKY_CRITICAL_ERROR(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::CRITICAL_ERROR, msg);
#define SKY_ASSERT_ERROR(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::ASSERT_ERROR, msg);
#define SKY_WARNING(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::WARNING, msg);
#define SKY_INFO(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::INFO, msg);
#define SKY_MEMORY_ALLOCATION(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::MEMORY_ALLOCATION, msg);
#define SKY_MEMORY_DELETION(logChannel, msg) skyLogDispatcher::Write(logChannel, skyLogLevel::MEMORY_DELETION, msg);
#else
#define SKY_FATAL_ERROR(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_CRITICAL_ERROR(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_ASSERT_ERROR(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_WARNING(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_INFO(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_MEMORY_ALLOCATION(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#define SKY_MEMORY_DELETION(logChannel, msg) do { (void)sizeof(msg); } while(0) 
#endif

//-----------------------------------------------------------------------------
// Public enumerations
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyLogger (Class)
/// <summary>
/// Wrapper functionality in order to successfully dispatch log messages     
/// to the corresponding log channels. Logging system makes use of           
/// intrusive list which has the benefit of being saved in the BSS and       
/// SDATA sections and therefore is available long before all the main       
/// initialization stuff on the stack.                                       
/// Logging classes has been fully switched to stack based allocations       
/// without a singleton in order to provide more than one log channel and    
/// thus we can declare multiple log classes such as NetworkLog, ConsoleLog, 
/// FileLog and so on. 
/// </summary>
//-----------------------------------------------------------------------------
class skyLogDispatcher
{
public:
	//-------------------------------------------------------------------------
    // Public Static Methods
    //-------------------------------------------------------------------------
	static void skyLogDispatcher::Write (unsigned int logChannel, skyLogLevel logLevel, std::string logMessage );
	static std::string skyLogDispatcher::LogLevelToString ( skyLogLevel logLevel );
	static void skyLogDispatcher::Enable (unsigned int logChannel); 
	static void skyLogDispatcher::Disable (unsigned int logChannel); 
};
