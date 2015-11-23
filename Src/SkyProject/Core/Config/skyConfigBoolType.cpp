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
// Name : skyConfigBoolType.cpp												 //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The ConfigBoolType is used in order to store arbitrary bool values       //
/// and make them globally accessible from within the engine and your        //
/// game. You can even assign new config values in your game code by just    //
/// globally creating new objects on the stack.                              //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyConfigBoolType.h"


namespace skyConfig
{
	///////////////////////////////////////////////////////////////////////////////
	// BoolType Member Definitions
	///////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------
	//  Name : BoolType (Constructor)
	/// <summary>
	/// Creates a new instance of the bool type class. You can specify a name, 
	/// description and the value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	BoolType::BoolType ( const char* name, const char* description, bool value )
	{
		this->mName = name;
		this->mDescription = description;
		this->mValue = value;

		this->AddToList ();

		SKY_PRINT_CONSOLE("SkyConfig", "Config (" + skyToString(name) + ") loaded into memory.", 0x0C);
	}

	//-----------------------------------------------------------------------------
	//  Name : operator= (Operator)
	/// <summary>
	/// Overloaded assign operator. This is used in order to convienantly assign
	/// new values to the config class.
	/// </summary>
	//-----------------------------------------------------------------------------
	BoolType& BoolType::operator=(bool value)
	{	
		this->mValue = value;
		
		return *this;
	}

	//-----------------------------------------------------------------------------
	//  Name : FindConfig (Method)
	/// <summary>
	/// Is used in order to find a config value in the intrusive list by its 
	/// config name.
	/// </summary>
	//-----------------------------------------------------------------------------
	BoolType* BoolType::FindConfig ( const char* name )
	{
		if(pBoolTypeHead != nullptr)
		{
			if ( pBoolTypeHead->mName == name )
			{
				return pBoolTypeHead;
			}

			BoolType* pNode = pBoolTypeHead->pNext;

			while(pNode != nullptr)
			{
				if(pNode->mName == name)
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
	/// Adds this instance to the list.
	/// </summary>
	//-----------------------------------------------------------------------------
	void BoolType::AddToList ( void )
	{
		if (pIntTypeHead)
		{
			pBoolTypeTail->pNext = this;
			pBoolTypeTail = this;
		}
		else
		{
			pBoolTypeHead = this;
			pBoolTypeTail = this;
		}
	}
};