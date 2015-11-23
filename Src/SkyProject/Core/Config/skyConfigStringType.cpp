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
// Name : skyConfigStringType.cpp											 //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The ConfigStringType is used in order to store arbitrary string values   //
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
#include "skyConfigStringType.h"


namespace skyConfig
{
	///////////////////////////////////////////////////////////////////////////////
	// IntType Member Definitions
	///////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------
	//  Name : StringType (Constructor)
	/// <summary>
	/// Creates a new instance of the string type class. You can specify a name, 
	/// description and the value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	StringType::StringType ( const char* name, const char* description, const char* value )
	{
		this->mName = name;
		this->mDescription = description;
		this->mValue = const_cast<char*>(value);
		this->mHasChanged = false;

		this->AddToList ();

		SKY_PRINT_CONSOLE("SkyConfig", "Config (" + skyToString(name) + ") loaded into memory.", 0x0C);
	}

	StringType::~StringType ()
	{
		if(mHasChanged)
			SKY_SAFE_DELETE_ARRAY(this->mValue);
	}

	//-----------------------------------------------------------------------------
	//  Name : operator= (Operator)
	/// <summary>
	/// Overloaded assign operator. This is used in order to convienantly assign
	/// new values to the config class.
	/// </summary>
	//-----------------------------------------------------------------------------
	StringType& StringType::operator=(const char* value)
	{
		size_t fileSize = strlen(value);

		this->mValue = SKY_NEW char[fileSize];
		//(this->mValue, value, fileSize);
		strncpy(this->mValue, value, fileSize);
		
		this->mValue[fileSize] = '\0';
		mHasChanged = true;

		return *this;
	}

	//-----------------------------------------------------------------------------
	//  Name : FindConfig (Method)
	/// <summary>
	/// Is used in order to find a config value in the intrusive list by its 
	/// config name.
	/// </summary>
	//-----------------------------------------------------------------------------
	StringType* StringType::FindConfig ( const char* name )
	{
		if(pIntTypeHead != nullptr)
		{
			if ( pStringTypeHead->mName == name )
			{
				return pStringTypeHead;
			}

			StringType* pNode = pStringTypeHead->pNext;

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
	void StringType::AddToList ( void )
	{
		if (pStringTypeHead)
		{
			pStringTypeTail->pNext = this;
			pStringTypeTail = this;
		}
		else
		{
			pStringTypeHead = this;
			pStringTypeTail = this;
		}
	}
};