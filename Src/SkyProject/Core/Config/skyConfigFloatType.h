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
// Name : skyConfigFloatType.h												 //
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


namespace skyConfig
{
	//-----------------------------------------------------------------------------
	// Main Class Declarations
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : FloatType (Class)
	/// <summary>
	/// An float type config class use it whenever you want to save a float 
	/// value in the global configuration. You can specify a min and max value 
	/// if you want. Besides its possible to just assign a new value by 
	/// using the normal assign for a float. 
	/// </summary>
	//-----------------------------------------------------------------------------
	class FloatType
	{
	public:
		//-------------------------------------------------------------------------
		// Constructor & Destructor
		//-------------------------------------------------------------------------
		FloatType::FloatType ( const char* name, const char* description, float value );
		FloatType::FloatType ( const char* name, const char* description, float value, 
							float minValue, float maxValue ); 

		//-------------------------------------------------------------------------
		// Operators
		//-------------------------------------------------------------------------
		FloatType& FloatType::operator =(float value);
		inline operator float(void) const { return this->mValue; } 

		//-------------------------------------------------------------------------
		// Public Static Members
		//-------------------------------------------------------------------------
		static FloatType* FloatType::FindConfig ( const char* name );

	private: 
		//-------------------------------------------------------------------------
		// Private Members
		//-------------------------------------------------------------------------
		FloatType* pNext; 
		const char* mName;
		const char* mDescription;

		float mValue;
		float mMinValue;
		float mMaxValue;

		//-------------------------------------------------------------------------
		// Private Methods
		//-------------------------------------------------------------------------
		void FloatType::AddToList ( void );

	};

	//-----------------------------------------------------------------------------
	// Intrusive List declarations
	//-----------------------------------------------------------------------------
	static FloatType* pFloatTypeHead = nullptr; 
	static FloatType* pFloatTypeTail = nullptr;
};