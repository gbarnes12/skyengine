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
// Name : skyHashedString.h                                                  //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Used to hash strings. The class has been taken from Game Coding          //
/// Complete. This is based adler32 checksum by Mark Adler                   //
/// </summary>                                                               //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //


//-------------------------------------------------------------------------
// Defines to make life easier
//-------------------------------------------------------------------------
#pragma warning(push)
#pragma warning(disable : 4311)

//-----------------------------------------------------------------------------
//  Name : skyHashedString (Class)
/// <summary>
/// Generates a unsigned long hash value for a string which we pass to it. 
/// This class has been taken from Game Coding Complete.
/// </summary>
//-----------------------------------------------------------------------------
class skyHashedString
{
public:
	//-------------------------------------------------------------------------
    // Constructors & Destructors
    //-------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : skyHashedString (Constructor)
	/// <summary>
	/// Creates a new instance of a hashed string with a char* string as parameter.
	/// </summary>
	//-----------------------------------------------------------------------------
	explicit skyHashedString(char const * const pIdentString) : 
		mIdent( HashName( pIdentString ) ), sIdentStr( pIdentString )
	{
	}

	//-------------------------------------------------------------------------
    // Public functions
    //-------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//  Name : GetHashValue (Function)
	/// <summary>
	/// Returns the hash value of the passed string.
	/// </summary>
	//-----------------------------------------------------------------------------
	unsigned long GetHashValue( void ) const
    {
		return reinterpret_cast<unsigned long>( mIdent );
    }

	//-----------------------------------------------------------------------------
	//  Name : GetStr (Function)
	/// <summary>
	/// Returns the string itself. 
	/// </summary>
	//-----------------------------------------------------------------------------
    const std::string & GetStr() const
    {
		return sIdentStr;
    }

	//-------------------------------------------------------------------------
    // Public static functions
    //-------------------------------------------------------------------------
    static void * HashName( char const *  pIdentStr );

	//-------------------------------------------------------------------------
    // Public operator functions
    //-------------------------------------------------------------------------
    bool operator< ( skyHashedString const & o ) const
    {
		bool r = ( GetHashValue() < o.GetHashValue() );
		return r;
    }

    bool operator== ( skyHashedString const & o ) const
    {
		bool r = ( GetHashValue() == o.GetHashValue() );
		return r;
    }

private:

	//-------------------------------------------------------------------------
    // Private members
    //-------------------------------------------------------------------------

	// note: m_ident is stored as a void* not an int, so that in
	// the debugger it will show up as hex-values instead of
	// integer values. This is a bit more representative of what
	// we're doing here and makes it easy to allow external code
	// to assign event types as desired.

	void * mIdent;
	std::string  sIdentStr;
};

//Remove the warning for warning #4311...
#pragma warning(pop)
