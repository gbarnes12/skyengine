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
// Name : skyConfigIntType.cpp												 //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The ConfigIntType is used in order to store arbitrary integer values     //
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
#include "skyConfigIntType.h"


namespace skyConfig
{
	///////////////////////////////////////////////////////////////////////////////
	// IntType Member Definitions
	///////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------
	//  Name : IntType (Constructor)
	/// <summary>
	/// Creates a new instance of the int type class. You can specify a name, 
	/// description and the value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	IntType::IntType ( const char* name, const char* description, int value )
	{
		this->mName = name;
		this->mDescription = description;
		this->mValue = value;
		this->mMinValue = -1;
		this->mMaxValue = -1;

		this->AddToList ();

		SKY_PRINT_CONSOLE("SkyConfig", "Config (" + skyToString(name) + ") loaded into memory.", 0x0C);
	}

	//-----------------------------------------------------------------------------
	//  Name : IntType (Constructor)
	/// <summary>
	/// Creates a new instance of the int type class. You can specify a name, 
	/// description, value, a min value and the max value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	IntType::IntType ( const char* name, const char* description, int value, 
								int minValue, int maxValue )
							
	{
		this->mName = name;
		this->mDescription = description;
		this->mMinValue = minValue;
		this->mMaxValue = maxValue;

		if (value < this->mMinValue)
		{
			value = this->mMinValue;
		}
		else if (value > this->mMaxValue)
		{
			value = this->mMaxValue;
		}
		
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
	IntType& IntType::operator=(int value)
	{
		if(this->mMinValue != -1 && this->mMaxValue != -1)
		{
			if (value < this->mMinValue)
			{
				SKY_WARNING(0, "IntType Config: Could not set value " + skyToString(value) + " for setting \"" + this->mName + "\" because it is smaller than the minimum. It will be set to " + skyToString(this->mMinValue) + ".");
				value = this->mMinValue;
			}
			else if (value > this->mMaxValue)
			{
				SKY_WARNING(0, "IntType Config: Could not set value " + skyToString(value) + " for setting \"" + this->mName + "\" because it is greater than the maximum. It will be set to " + skyToString(this->mMaxValue) + ".");
				value = this->mMaxValue;
			}
		}
		
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
	IntType* IntType::FindConfig ( const char* name )
	{
		if(pIntTypeHead != nullptr)
		{
			if ( pIntTypeHead->mName == name )
			{
				return pIntTypeHead;
			}

			IntType* pNode = pIntTypeHead->pNext;

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
	void IntType::AddToList ( void )
	{
		if (pIntTypeHead)
		{
			pIntTypeTail->pNext = this;
			pIntTypeTail = this;
		}
		else
		{
			pIntTypeHead = this;
			pIntTypeTail = this;
		}
	}
};