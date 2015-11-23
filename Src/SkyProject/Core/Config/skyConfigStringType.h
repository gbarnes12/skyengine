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
// Name : skyConfigStringType.h												 //
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


namespace skyConfig
{
	//-----------------------------------------------------------------------------
	// Main Class Declarations
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : StringType (Class)
	/// <summary>
	/// A string type config class use it whenever you want to save an std::string 
	/// value in the global configuration. Besides its possible to just assign a new value 
	/// by using the normal assign for a string. 
	/// </summary>
	//-----------------------------------------------------------------------------
	class StringType
	{
	public:
		//-------------------------------------------------------------------------
		// Constructor & Destructor
		//-------------------------------------------------------------------------
		StringType::StringType ( const char* name, const char* descriptionconst, const char* value );
		StringType::~StringType ();

		//-------------------------------------------------------------------------
		// Operators
		//-------------------------------------------------------------------------
		StringType& StringType::operator =(const  char* value);
		inline operator const char* (void) const { return this->mValue; } 

		//-------------------------------------------------------------------------
		// Public Static Members
		//-------------------------------------------------------------------------
		static StringType* StringType::FindConfig ( const char* name );

	private: 
		//-------------------------------------------------------------------------
		// Private Members
		//-------------------------------------------------------------------------
		StringType* pNext; 
		const char* mName;
		const char* mDescription;
		bool mHasChanged;
		char* mValue;
		
		//-------------------------------------------------------------------------
		// Private Methods
		//-------------------------------------------------------------------------
		void StringType::AddToList ( void );
	};

	//-----------------------------------------------------------------------------
	// Intrusive List declarations
	//-----------------------------------------------------------------------------
	static StringType* pStringTypeHead = nullptr; 
	static StringType* pStringTypeTail = nullptr;
};