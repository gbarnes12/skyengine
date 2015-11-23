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
	//  Name : Vector3Type (Class)
	/// <summary>
	/// An vector3 type config class use it whenever you want to save a vector3 
	/// value in the global configuration. 
	/// Besides its possible to just assign a new value by 
	/// using the normal assign for a bool. 
	/// </summary>
	//-----------------------------------------------------------------------------
	class Vector3Type
	{
	public:
		//-------------------------------------------------------------------------
		// Constructor & Destructor
		//-------------------------------------------------------------------------
		Vector3Type::Vector3Type ( const char* name, const char* description, skyVector3 value );

		//-------------------------------------------------------------------------
		// Operators
		//-------------------------------------------------------------------------
		Vector3Type& Vector3Type::operator=(skyVector3 value);
		inline operator skyVector4(void) const { return skyVector4(this->mValue); } 
		//inline operator skyVector3(void) const { return this->mValue; } 

		//-------------------------------------------------------------------------
		// Public Static Members
		//-------------------------------------------------------------------------
		static Vector3Type* Vector3Type::FindConfig ( const char* name );

	private: 
		//-------------------------------------------------------------------------
		// Private Members
		//-------------------------------------------------------------------------
		Vector3Type* pNext; 
		const char* mName;
		const char* mDescription;
		skyVector3 mValue;

		//-------------------------------------------------------------------------
		// Private Methods
		//-------------------------------------------------------------------------
		void Vector3Type::AddToList ( void );

	};

	//-----------------------------------------------------------------------------
	// Intrusive List declarations
	//-----------------------------------------------------------------------------
	static Vector3Type* pVector3TypeHead = nullptr; 
	static Vector3Type* pVector3TypeTail = nullptr;
};