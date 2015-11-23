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
// Name : skyLogs.h														     //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Global declaration file in order to create new log types. As a           //
/// parameter you need to specify a channel on which this log file will      //
/// listen to.                                                               //
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
#include "Logs\skyFileLog.h"
#include "Logs\skyHTMLLog.h" 
#include "Logs\skyNetworkLog.h"

namespace skyLog
{
	extern skyFileLog g_FileLog;
	extern skyHTMLLog g_HTMLLog;
	extern skyNetworkLog g_NetworkLog;
};
