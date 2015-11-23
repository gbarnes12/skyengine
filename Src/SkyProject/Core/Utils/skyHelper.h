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
// Name : skyHelper.h                                                        //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// You may find some helpful functions within this source file:             //
///	hardware identifikation, date time functions and so on.                  //
/// </summary>                                                               //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Constant definitions
//-----------------------------------------------------------------------------
const float DEG2RAD = 3.141593f / 180;
const float RAD2DEG = 180 / 3.141593f;


//-----------------------------------------------------------------------------
// just a type definition for the struct tm which is 
// a representation for date and time.
//-----------------------------------------------------------------------------
typedef std::vector <std::string> skyStringVec;


//-----------------------------------------------------------------------------
//  Name : skyRad2Deg (Function)
/// <summary>
/// Converts radians into degrees
/// </summary>
//-----------------------------------------------------------------------------
float skyRad2Deg(float radians);

//-----------------------------------------------------------------------------
//  Name : skyDeg2Rad (Function)
/// <summary>
/// Converts degrees into radians
/// </summary>
//-----------------------------------------------------------------------------
float skyDeg2Rad(float degree);

//-----------------------------------------------------------------------------
//  Name : skyString2WString (Function)
/// <summary>
/// Converts a string to a wstring
/// </summary>
//-----------------------------------------------------------------------------
std::wstring skyString2WString(const std::string& str);

//-----------------------------------------------------------------------------
//  Name : skyClamp (Function)
/// <summary>
/// Converts a string to a wstring
/// </summary>
//-----------------------------------------------------------------------------
skyFloat skyClamp(skyFloat a, skyFloat min, skyFloat max);

//-----------------------------------------------------------------------------
//  Name : skyWString2String (Function)
/// <summary>
/// Converts a wstring to a string
/// </summary>
//-----------------------------------------------------------------------------
std::string skyWString2String(const std::wstring& s);

//-----------------------------------------------------------------------------
//  Name : skyWildcardMatch (Function)
/// <summary>
/// Checks whether a specific wildcard matches
/// </summary>
//-----------------------------------------------------------------------------
BOOL skyWildcardMatch(const char *pat, const char *str);
BOOL skyWideWildcardMatch(skyWideStr pat, skyWideStr str);

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console. Use hex values for color: 
/// 0x0F = Black background and white color
/// </summary>
//-----------------------------------------------------------------------------
std::string skyExtractDirectory( const std::string& path );

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console. Use hex values for color: 
/// 0x0F = Black background and white color
/// </summary>
//-----------------------------------------------------------------------------
std::string skyExtractFilename( const std::string& path );

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_NET (Function)
/// <summary>
/// Prints a string to the console. Use hex values for color: 
/// 0x0F = Black background and white color
/// </summary>
//-----------------------------------------------------------------------------
std::string skyChangeExtension( const std::string& path, const std::string& ext );

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_CONSOLE (Function)
/// <summary>
/// Prints a string to the console. Use hex values for color: 
/// 0x0F = Black background and white color
/// </summary>
//-----------------------------------------------------------------------------
inline void skyPrintToConsole(std::string type, std::string msg, int classColor, std::string function, std::string file, int line);


//-----------------------------------------------------------------------------
//  Name : skyPrintFromScript (Function)
/// <summary>
/// Prints message from script
/// </summary>
//-----------------------------------------------------------------------------
void skyPrintFromScript(std::string msg);

//-----------------------------------------------------------------------------
//  Name : skyToBool (Function)
/// <summary>
/// Casts a string to a bool value. The string can either be 1 / 0 or true / false
/// </summary>
//-----------------------------------------------------------------------------
bool skyToBool( const std::string & s );

//-----------------------------------------------------------------------------
//  Name : skySplit (Function)
/// <summary>
/// Splits a string by the delimeter into a vector of strings.  For example, say you have the following string:
/// std::string test("one,two,three");
/// You could call Split() like this:
/// Split(test, outVec, ',');
/// outVec will have the following values:
/// "one", "two", "three"
/// </summary>
//-----------------------------------------------------------------------------
void skySplit(const std::string& str, skyStringVec& vec, char delimiter);

//-----------------------------------------------------------------------------
//  Name : skyPointInPlane (Function)
/// <summary>
/// Checks whether a vector is within a 2d plane or not!
/// </summary>
//-----------------------------------------------------------------------------
//bool skyPointInPlane(skyVector2 mouse, skyVector4 plane);


//-----------------------------------------------------------------------------
//  Name : skyTransformVector3 (Function)
/// <summary>
/// Transforms a vector by a given matrix!
/// </summary>
//-----------------------------------------------------------------------------
//skyVector3 skyTransformVector3 ( skyVector3 pPosition, skyMatrix4 pMatrix);

//-----------------------------------------------------------------------------
//  Name : skyWCharToString (Function)
/// <summary>
/// Converts a wchar_t* to a string! Found at 
/// http://stackoverflow.com/questions/4339960/how-do-i-convert-wchar-t-to-stdstring
/// </summary>
//-----------------------------------------------------------------------------
std::string skyWCharToString( const wchar_t *s, char dfault, const std::locale& loc );

//-----------------------------------------------------------------------------
//  Name : skyStringExplode (Function)
/// <summary>
/// Explodes a given string into pieces by separator. Stores the results in a 
/// vector. Found at:
/// http://www.infernodevelopment.com/perfect-c-string-explode-split
/// </summary>
//-----------------------------------------------------------------------------
void skyStringExplode(std::string str, std::string separator, std::vector<std::string>* results);


//-----------------------------------------------------------------------------
//  Name : skyTimeStruct (struct)
/// <summary>
/// Time structure containing the following attributes:
///
/// Second
///		Seconds after minute (0 – 59).
/// Minute
///		Minutes after hour (0 – 59).
/// Hour
///		Hours after midnight (0 – 23).
/// DayOfMonth
///		Day of month (1 – 31).
/// Month
///		Month (0 – 11; January = 0).
/// Year
///		Year (current year minus 1900).
/// DayOfWeek
///		Day of week (0 – 6; Sunday = 0).
/// DayOfYear
///		Day of year (0 – 365; January 1 = 0).
/// ISDST
///		Positive value if daylight saving time is in effect; 0 if daylight saving time is not in effect; 
///		negative value if status of daylight saving time is unknown. If the TZ environment variable is set, 
///		the C run-time library assumes rules appropriate to the United States for implementing the calculation of daylight saving time (DST).
/// </summary>
//-----------------------------------------------------------------------------
struct skyTimeStruct
{
	int Hour;
	int ISDST;
	int DayOfMonth;
	int Minute;
	int Month;
	int Second;
	int DayOfWeek;
	int Year;
	int DayOfYear;

	skyTimeStruct::skyTimeStruct()
	{
		this->Hour = 0;
		this->ISDST = 0;
		this->DayOfMonth = 0;
		this->Minute = 0;
		this->Month = 0;
		this->Second = 0;
		this->DayOfWeek = 0;
		this->Year = 0;
		this->DayOfYear = 0;
	}
};

//-----------------------------------------------------------------------------
//  Name : SKY_PRINT_CONSOLE (Function)
/// <summary>
/// Prints a string to a attached network application if enabled
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyPrintToNetwork(skyLogLevel a_eLevel, std::string msg, std::string function, std::string file, int line);

//-----------------------------------------------------------------------------
//  Name : skyHasFlag (Function)
/// <summary>
/// Has flag
/// </summary>
//-----------------------------------------------------------------------------
skyBool skyHasFlag( skyULong a_ulBitset, skyULong a_ulFlag );

/*
//-----------------------------------------------------------------------------
//  Name : skyCreateInputLayoutDescFromVertexShaderSignature (struct)
/// <summary>
/// 
/// </summary>
//-----------------------------------------------------------------------------
HRESULT skyCreateInputLayoutDescFromVertexShaderSignature( ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout );*/
