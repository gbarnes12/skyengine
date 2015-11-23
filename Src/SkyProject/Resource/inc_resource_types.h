#pragma once

typedef struct sResourceInfo 
{
	skyULong m_ulHash;
	skyString m_strFileName;
	skyString m_strFilePath;
	skyString m_strFileExtension;
	skyUInt m_u32FileSizeRaw;
	skyUInt m_u32FileSizeCompiled;
	time_t m_u32DateTimeRaw;
	time_t m_u32DateTimeCompiled;
	skyBool m_bSuccess;
	skyString m_strType;
} sResourceInfo;

typedef enum eResourceRequestMode
{
	eResourceRequestMode_Immediate = 0,
	eResourceRequestMode_Deferred = 1
} eResourceRequestMode;

typedef enum eResourceMode 
{
	eResourceMode_Raw = 0,
	eResourceMode_Compiled = 1,
	eResourceMode_Pak = 2
} eResourceMode;

typedef enum eResourceState
{
	eResourceState_Created = 0,
	eResourceState_Loaded = 1,
	eResourceState_CachedIn = 2,
	eResourceState_CachedOut = 3
} eResourceState;