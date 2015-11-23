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
// Name : skyConfigBoolType.h												 //
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


namespace skyConfig
{
	//-----------------------------------------------------------------------------
	// Main Class Declarations
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : BoolType (Class)
	/// <summary>
	/// An bool type config class use it whenever you want to save a bool 
	/// value in the global configuration. 
	/// Besides its possible to just assign a new value by 
	/// using the normal assign for a bool. 
	/// </summary>
	//-----------------------------------------------------------------------------
	class BoolType
	{
	public:
		//-------------------------------------------------------------------------
		// Constructor & Destructor
		//-------------------------------------------------------------------------
		BoolType::BoolType ( const char* name, const char* description, bool value );

		//-------------------------------------------------------------------------
		// Operators
		//-------------------------------------------------------------------------
		BoolType& BoolType::operator=(bool value);
		inline operator bool(void) const { return this->mValue; } 

		//-------------------------------------------------------------------------
		// Public Static Members
		//-------------------------------------------------------------------------
		static BoolType* BoolType::FindConfig ( const char* name );

	private: 
		//-------------------------------------------------------------------------
		// Private Members
		//-------------------------------------------------------------------------
		BoolType* pNext; 
		const char* mName;
		const char* mDescription;
		bool mValue;

		//-------------------------------------------------------------------------
		// Private Methods
		//-------------------------------------------------------------------------
		void BoolType::AddToList ( void );

	};

	//-----------------------------------------------------------------------------
	// Intrusive List declarations
	//-----------------------------------------------------------------------------
	static BoolType* pBoolTypeHead = nullptr; 
	static BoolType* pBoolTypeTail = nullptr;
};