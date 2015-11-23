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
// Name : skyConfigIntType.h												 //
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


namespace skyConfig
{
	//-----------------------------------------------------------------------------
	// Main Class Declarations
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : IntType (Class)
	/// <summary>
	/// An int type config class use it whenever you want to save an integer 
	/// value in the global configuration. You can specify a min and max value 
	/// if you want. Besides its possible to just assign a new value by 
	/// using the normal assign for an integer. 
	/// </summary>
	//-----------------------------------------------------------------------------
	class IntType
	{
	public:
		//-------------------------------------------------------------------------
		// Constructor & Destructor
		//-------------------------------------------------------------------------
		IntType::IntType ( const char* name, const char* description, int value );
		IntType::IntType ( const char* name, const char* description, int value, 
							int minValue, int maxValue ); 

		//-------------------------------------------------------------------------
		// Operators
		//-------------------------------------------------------------------------
		IntType& IntType::operator =(int value);
		inline operator int(void) const { return this->mValue; } 

		//-------------------------------------------------------------------------
		// Public Static Members
		//-------------------------------------------------------------------------
		static IntType* IntType::FindConfig ( const char* name );

	private: 
		//-------------------------------------------------------------------------
		// Private Members
		//-------------------------------------------------------------------------
		IntType* pNext; 
		const char* mName;
		const char* mDescription;

		int mValue;
		int mMinValue;
		int mMaxValue;

		//-------------------------------------------------------------------------
		// Private Methods
		//-------------------------------------------------------------------------
		void IntType::AddToList ( void );
	};

	//-----------------------------------------------------------------------------
	// Intrusive List declarations
	//-----------------------------------------------------------------------------
	static IntType* pIntTypeHead = nullptr; 
	static IntType* pIntTypeTail = nullptr;
};