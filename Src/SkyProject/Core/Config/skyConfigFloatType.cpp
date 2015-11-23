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
// Name : skyConfigFloatType.cpp											 //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The ConfigFloatType is used in order to store arbitrary float values     //
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
#include "skyConfigFloatType.h"


namespace skyConfig
{
	///////////////////////////////////////////////////////////////////////////////
	// FloatType Member Definitions
	///////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------
	//  Name : FloatType (Constructor)
	/// <summary>
	/// Creates a new instance of the int type class. You can specify a name, 
	/// description and the value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	FloatType::FloatType ( const char* name, const char* description, float value )
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
	//  Name : FloatType (Constructor)
	/// <summary>
	/// Creates a new instance of the int type class. You can specify a name, 
	/// description, the value. the min value and the max value you want to have.
	/// </summary>
	//-----------------------------------------------------------------------------
	FloatType::FloatType ( const char* name, const char* description, float value, 
								float minValue, float maxValue )
							
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
	FloatType& FloatType::operator=(float value)
	{
		if(this->mMinValue != -1 && this->mMaxValue != -1)
		{
			if (value < this->mMinValue)
			{
				SKY_WARNING(0, "IntType Config: Could not set value " + skyToString(value) + " for setting \"" + skyToString(this->mName) + "\" because it is smaller than the minimum. It will be set to " + skyToString(this->mMinValue) + ".");
				value = this->mMinValue;
			}
			else if (value > this->mMaxValue)
			{
				SKY_WARNING(0, "IntType Config: Could not set value " + skyToString(value) + " for setting \"" + skyToString(this->mName) + "\" because it is greater than the maximum. It will be set to " + skyToString(this->mMaxValue) + ".");
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
	FloatType* FloatType::FindConfig ( const char* name )
	{
		if(pFloatTypeHead != nullptr)
		{
			if ( pFloatTypeHead->mName == name )
			{
				return pFloatTypeHead;
			}

			FloatType* pNode = pFloatTypeHead->pNext;

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
	void FloatType::AddToList ( void )
	{
		if (pFloatTypeHead)
		{
			pFloatTypeTail->pNext = this;
			pFloatTypeTail = this;
		}
		else
		{
			pFloatTypeHead = this;
			pFloatTypeTail = this;
		}
	}
};