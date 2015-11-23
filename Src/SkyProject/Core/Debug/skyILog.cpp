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
#include "stdafx.h" 
#include "skyILog.h"

///////////////////////////////////////////////////////////////////////////////
// skyGameApplication Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : FindLog (Method)
/// <summary>
/// Finds a specific log file with its channel id.
/// </summary>
//-----------------------------------------------------------------------------
skyILog* skyILog::FindLog ( unsigned int channelID )
{
	if(pLogListHead != nullptr)
	{
		if ( pLogListHead->mChannelId == channelID )
		{
			return pLogListHead;
		}

		skyILog* pNode = pLogListHead->pNext;

		while(pNode != nullptr)
		{
			if(pNode->mChannelId == channelID)
			{
				return pNode;
			}

			pNode = pNode->pNext;
		}
	}

	return nullptr;
}

//-----------------------------------------------------------------------------
//  Name : AddToList (Method)
/// <summary>
/// Adds this log to the intrusive list.
/// </summary>
//-----------------------------------------------------------------------------
void skyILog::AddToList ( void )
{
	if (pLogListHead)
	{
		pLogListTail->pNext = this;
		pLogListTail = this;
	}
	else
	{
		pLogListHead = this;
		pLogListTail = this;
	}
}