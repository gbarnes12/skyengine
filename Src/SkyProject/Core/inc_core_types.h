#pragma once
#include <iostream>


typedef enum eSkyResult
{
	SKY_OK				= 0,		// Success
	SKY_ERROR			= 1,		// Common Error
	SKY_CANCELED		= 2,		// Action aborted
	SKY_NOT_FOUND		= 3,		// Not found
	SKY_WARNING			= 4,		// Warning
	SKY_STOP			= 5,		// Stop
	SKY_NOT_SUPPORTED	= 6,		// Not Supported in case some one tries to start the engine with a too weak hardware
	SKY_ALREADY_EXISTS	= 7,			// throw this if something already exists!
	SKY_OUT_OF_MEMORY   = 8,
	SKY_TOO_LARGE       = 9,
	SKY_INVALID_POINTER = 10,
	SKY_INVALID_CAST    = 11,
	SKY_NOT_IMPLEMENTED = 12
} eSkyResult;

typedef eSkyResult skyResult;

typedef enum eLogLevel
{
	FATAL_ERROR = 0,
	CRITICAL_ERROR = 1,
	ASSERT_ERROR = 2,
	WARNING = 3,
	INFO = 4,
	MEMORY_ALLOCATION = 5,
	MEMORY_DELETION = 6
} eLogLevel;

typedef eLogLevel skyLogLevel;

typedef enum eLogChannel
{
	TXT_FILE = 0,
	HTML_FILE = 1,
	CONSOLE = 2,
	NETWORK = 3
} eLogChannel;

typedef eLogChannel skyLogChannel;

typedef enum eFileMode
{
	eFileMode_Read = 0x01,
	eFileMode_Write = 0x02, 
	eFileMode_Recreate = 0x05,
	eFileMode_Append = 0x08,
	eFileMode_Binary = 0x10,
	eFileMode_Ascii = 0x20
} eFileMode;

typedef eFileMode skyFileMode;

typedef enum eLoadMode 
{
	eLoadMode_FromFile = 1,
	eLoadMode_FromMemory = 2
} eLoadMode;




//-----------------------------------------------------------------------------
// Typedefinition (Datatypes)
//-----------------------------------------------------------------------------
typedef int skyInt; 
typedef long skyLong;
typedef unsigned long skyULong; 
typedef unsigned int skyUInt; 
typedef float skyFloat; 
typedef char skyAnsiChar; 
typedef unsigned char skyUAnsiChar;
typedef char skyAnsiChar;
typedef const char* skyAnsiStr;
typedef std::string skyString;
typedef double skyDouble;
typedef void skyVoid;
typedef void* skyVoidPtr;
typedef bool skyBool;
typedef wchar_t skyWideChar;
typedef const wchar_t* skyWideStr;
typedef std::wstring skyWString;


//-----------------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------------
typedef struct sIOFileInfo
{
	time_t    m_i64ATime;     /* Datum des letzten Zugriffs */
    time_t    m_i64CTime;     /* Datum der letzten Statusänderung */
    time_t    m_i64MTime;     /* Datum der letzten Modifikation */
    skyLong   m_lSize;       /* Dateigröße in Byte */
} sIOFileInfo;
 
struct sIOMemBlob
{
	uintptr_t m_uiBufferPtr;
	size_t m_uiBufferSize;
};


//-----------------------------------------------------------------------------
// Define (Datatypes)
//-----------------------------------------------------------------------------
#define SKY_TRUE true
#define SKY_FALSE false
#define SKY_NULL NULL

//-----------------------------------------------------------------------------
// NEW Definition
//-----------------------------------------------------------------------------
#if !defined(SKY_BUILD_MASTER)
#define SKY_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define SKY_NEW new
#endif