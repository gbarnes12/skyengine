#include "stdafx.h"
#include <stack>
#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf
#include "..\System\skyResourceSystem.h"
#include "skyResourceDatabase.h"


SKY_TODO("move this to platform independent area!");
SKY_TODO("create a thread class which can be inherited from! Create a better critical section class without this unneccessary interface stuff!.");
// Code from http://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c
bool skyListFiles(skyWString a_wstrPath, skyWString a_wstrMask, std::vector<skyWString>& a_arrFiles) 
{
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    skyWString wstrSpec;
    std::stack<skyWString> arrDirectories;

    arrDirectories.push(a_wstrPath);
    a_arrFiles.clear();

	int u32Layer = 0;

    while (!arrDirectories.empty()) 
	{
		
        a_wstrPath = arrDirectories.top();
        wstrSpec = a_wstrPath + L"\\*";
        arrDirectories.pop();

        hFind = FindFirstFile(wstrSpec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)  
		{
            return false;
        } 

        do 
		{
            if (wcscmp(ffd.cFileName, L".") != 0 && 
                wcscmp(ffd.cFileName, L"..") != 0) 
			{
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
					if(u32Layer == 0)
						arrDirectories.push(a_wstrPath + ffd.cFileName);
					else
						arrDirectories.push(a_wstrPath + L"\\" + ffd.cFileName);
		
                }
                else {
					skyWString wstrFilePath =  a_wstrPath + L"\\" + ffd.cFileName;
					if(skyWideWildcardMatch(a_wstrMask.c_str(), wstrFilePath.c_str())) 
					{
						a_arrFiles.push_back(wstrFilePath);
					}
                }
            }
        } 
		while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
		u32Layer++;
    }

    return true;
}


bool skyGetNextLineAndSplitIntoTokens(std::istream& a_ioInStream,  std::vector<skyString>& a_arrResults)
{
	a_arrResults.clear();
    skyString strLine;
    std::getline(a_ioInStream, strLine);

    std::stringstream  ioLineStream(strLine);
    skyString strCell;

    while(std::getline(ioLineStream, strCell,';'))
    {
        a_arrResults.push_back(strCell);
    }
	return (a_arrResults.size() > 0);
}


std::string skyGetDirectoryFromFileDirectory(const std::string& fname)
{
     size_t pos = fname.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : fname.substr(0, pos);
}


struct skyMatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\';
    }
};

struct skyMatchExtensionSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '.';
    }
};

std::string skyGetFileNameFromDirectory( std::string const& a_strPath )
{
    return std::string( 
        std::find_if( a_strPath.rbegin(), a_strPath.rend(),
                      skyMatchPathSeparator() ).base(),
        a_strPath.end() );
}

std::string skyGetFileExtension(std::string const& a_strFileName)
{
	return std::string( 
        std::find_if( a_strFileName.rbegin(), a_strFileName.rend(),
                      skyMatchExtensionSeparator() ).base(),
        a_strFileName.end() );
}

std::string skyGetTypeDirectory(std::string const& a_strPath)
{
	std::string path = a_strPath.substr(a_strPath.find_last_of("..") + 1, a_strPath.size()); 
	return path;
}

std::string skyGetFileNameWithoutExtension(std::string const& a_strFileName)
{
	return a_strFileName.substr(0, a_strFileName.find_first_of("."));
}


skyResult skyResourceDatabase::Initialize ( skyResourceSystem* a_pSystem )
{
	this->m_pSystem = a_pSystem;

	skyResult hr;
	m_csSecureMap = skyPlatform::CreateCriticalSection();

	// first step we need to read the database files (.db from compiled dir!)
	InitializeDirs();
	SKY_VR(LoadDatabaseFiles());
	SKY_VR(ScanRawDirectory());

	// update the datbase files
	SKY_VR(SaveDatabaseFiles());

	return SKY_OK;
}

skyResult skyResourceDatabase::Shutdown ( )
{
	m_mapResources.clear();
	SKY_SAFE_DELETE(m_csSecureMap);
	return SKY_OK;
}

skyVoid skyResourceDatabase::InitializeDirs()
{
	skyWString g_strDataDir = skyPlatform::GetExePath();
	skyUInt u32Pos = g_strDataDir.find(L"Game.exe");
	m_strDataDir = g_strDataDir.substr (0, u32Pos);

	m_strDataDir += L"..\\Data\\";
	m_strCompiledDir = m_strDataDir + L"Compiled\\";
	m_strRawDir =  m_strDataDir + L"Raw\\";
}

skyString skyResourceDatabase::GetTypeFromExtension(std::string const& a_strExtension)
{
	if(a_strExtension == "hlsl")
		return "Shader";
	else if ( a_strExtension == "jpg" || a_strExtension == "png" || a_strExtension == "bmp" || a_strExtension == "dds")
		return "Image";
	else if ( a_strExtension == "sm" ) 
		return "Mesh";
	else if ( a_strExtension == "sma" ) 
		return "SknMesh";
	else if ( a_strExtension == "mat" ) 
		return "Material";
	else if ( a_strExtension == "as" ) 
		return "Script";
	else if ( a_strExtension == "goprefab" ) 
		return "Prefab";

	return "Document";
}

SKY_TODO("The rechecking and reinserting of files doesn't work right! We need to adjust this");
skyResult skyResourceDatabase::ScanRawDirectory()
{
	std::vector<skyWString> arrDatabaseFiles;
	std::vector<sResourceInfo> arrResourceInfos;
	if(skyListFiles(m_strRawDir, L"*", arrDatabaseFiles))
	{
		for(skyUInt i = 0; i < arrDatabaseFiles.size(); i++)
		{
			skyString strFilePath (arrDatabaseFiles[i].begin(), arrDatabaseFiles[i].end());
			skyIFile* pFile = this->m_pSystem->m_FileSystem.Open("disk", strFilePath, eFileMode_Read);
			if(pFile)
			{
				sIOFileInfo sFileInfo;
				SKY_ZERO_MEM(&sFileInfo, sizeof(sIOFileInfo));

				if(skyPlatform::GetFileInfo(strFilePath, &sFileInfo)) 
				{
					skyString strDirectory = skyGetDirectoryFromFileDirectory(strFilePath);
					skyString strTypeDirectory = skyGetTypeDirectory(strDirectory);
					skyString strFileName = skyGetFileNameFromDirectory(strFilePath);
					skyString strFileExtension = skyGetFileExtension(strFileName);

					skyHashedString strHashedName((strFileName).c_str());
					skyULong ulHashedKey = strHashedName.GetHashValue();


					sResourceInfo* sResource = SKY_NEW sResourceInfo();
					sResource->m_strFileName = skyGetFileNameWithoutExtension(strFileName);
					sResource->m_strFilePath = strTypeDirectory;
					sResource->m_strFileExtension = strFileExtension;
					sResource->m_bSuccess = SKY_FALSE;
					sResource->m_ulHash = ulHashedKey;
					sResource->m_u32FileSizeRaw = pFile->VGetTotalSize();
					sResource->m_u32DateTimeRaw = sFileInfo.m_i64MTime;
					sResource->m_strType = this->GetTypeFromExtension(strFileExtension);
					arrResourceInfos.push_back(*sResource);
					SKY_SAFE_DELETE(sResource);
				}
			}

			this->m_pSystem->m_FileSystem.Close(pFile);
			pFile = NULL;
		}
	}

	// update database files
	for(skyUInt i = 0; i < arrResourceInfos.size(); i++)
	{
		sResourceInfo sInfo = arrResourceInfos[i];

		if(m_mapResources.find(sInfo.m_ulHash) == m_mapResources.end())
		{
			m_mapResources.insert(std::pair<skyULong, sResourceInfo>(sInfo.m_ulHash, sInfo));
		}
		
		sResourceInfo sInfoMapped = m_mapResources[sInfo.m_ulHash];
		sInfoMapped.m_strFilePath = sInfo.m_strFilePath;
		sInfoMapped.m_strFileName = sInfo.m_strFileName;
		sInfoMapped.m_u32FileSizeRaw = sInfo.m_u32FileSizeRaw;
		sInfoMapped.m_u32DateTimeRaw = sInfo.m_u32DateTimeRaw;
	}

	// recheck the raw files against database file if it still exists
	for(skyResourceInfoMap::iterator it = m_mapResources.begin(); it != m_mapResources.end(); it++)
	{
		sResourceInfo sInfo = (*it).second;
		skyBool bExists = SKY_FALSE;
		for(skyUInt i = 0; i < arrResourceInfos.size(); i++)
		{
			if(arrResourceInfos[i].m_ulHash == sInfo.m_ulHash)
			{
				bExists = SKY_TRUE;
				break;
			}
		}
		
		if(!bExists) {
			it = m_mapResources.erase(it);
		}
	}

	arrResourceInfos.clear();
	arrDatabaseFiles.clear();

	return SKY_OK;
}


skyResult skyResourceDatabase::SaveDatabaseFiles ( )
{
	std::map<skyString, std::vector<sResourceInfo>> mapDatabaseFiles;

	// fill map 
	this->m_csSecureMap->VLock();
	for(skyResourceInfoMap::iterator it = m_mapResources.begin(); it != m_mapResources.end(); it++)
	{
		sResourceInfo sInfo = (*it).second;
		
		if(mapDatabaseFiles.find(sInfo.m_strType) == mapDatabaseFiles.end())
			mapDatabaseFiles.insert(std::pair<skyString, std::vector<sResourceInfo>>(sInfo.m_strType, std::vector<sResourceInfo>()));

		mapDatabaseFiles[sInfo.m_strType].push_back(sInfo);
	}
	this->m_csSecureMap->VUnlock();

	//update files (replace)
	for(std::map<skyString, std::vector<sResourceInfo>>::iterator it = mapDatabaseFiles.begin(); it != mapDatabaseFiles.end(); it++)
	{
		skyString strType = (*it).first;
		std::vector<sResourceInfo> arrResources = (*it).second;
		eFileMode eMode = (eFileMode)(eFileMode_Write | eFileMode_Recreate);
		skyString strFileName = skyString(this->m_strCompiledDir.begin(), this->m_strCompiledDir.end()) + strType + "\\" + strType + ".db";
		skyIFile* pFile = this->m_pSystem->m_FileSystem.Open("disk", strFileName, eMode);
		if(pFile)
		{
			skyString strContent = "";
			for(skyUInt i = 0; i < arrResources.size(); i++)
			{
				sResourceInfo& sInfo = arrResources[i];

				strContent += skyToString(sInfo.m_ulHash) + ";";
				strContent += sInfo.m_strFileName + ";";
				strContent += sInfo.m_strFileExtension + ";";
				strContent += sInfo.m_strFilePath + ";";
				strContent += skyToString(sInfo.m_u32FileSizeRaw) + ";";
				strContent += skyToString(sInfo.m_u32FileSizeCompiled) + ";";
				strContent += skyToString(sInfo.m_u32DateTimeRaw) + ";";
				strContent += skyToString(sInfo.m_u32DateTimeCompiled) + ";";
				strContent += ((sInfo.m_bSuccess) ? "1" : "0");
				strContent += ";" + sInfo.m_strType + ";\n";
			}

			pFile->VWrite((void*)strContent.c_str(), strContent.size());
		}

		this->m_pSystem->m_FileSystem.Close(pFile);
	}

	mapDatabaseFiles.clear();

	return SKY_OK;
}

skyResult skyResourceDatabase::LoadDatabaseFiles ( )
{ 
	std::vector<skyWString> arrDatabaseFiles;

	if(skyListFiles(m_strCompiledDir, L"*.db", arrDatabaseFiles))
	{
		for(skyUInt i = 0; i < arrDatabaseFiles.size(); i++)
		{
			skyString strAnsiPath( arrDatabaseFiles[i].begin(), arrDatabaseFiles[i].end() );
			std::ifstream in(strAnsiPath.c_str());

			std::vector<skyString> columns;
			while(skyGetNextLineAndSplitIntoTokens(in, columns))
			{
				sResourceInfo* sInfo = SKY_NEW sResourceInfo();
				sInfo->m_ulHash = strtoul(columns[0].c_str(), NULL, 0); 
				sInfo->m_strFileName = columns[1];
				sInfo->m_strFileExtension = columns[2];
				sInfo->m_strFilePath = columns[3];
				sInfo->m_u32FileSizeRaw = atoi(columns[4].c_str());
				sInfo->m_u32FileSizeCompiled = atoi(columns[5].c_str());
				sInfo->m_u32DateTimeRaw = (__int64)atoi(columns[6].c_str());
				sInfo->m_u32DateTimeCompiled = (__int64)atoi(columns[7].c_str());
				sInfo->m_bSuccess = (columns[8] == "1") ? true : false;
				sInfo->m_strType = columns[9];
				m_mapResources.insert(std::pair<skyULong, sResourceInfo>(sInfo->m_ulHash, *sInfo));
				SKY_SAFE_DELETE(sInfo);
				columns.clear();
			}
			in.close();
		}
	}

	arrDatabaseFiles.clear();

	return SKY_OK;
}

skyResult skyResourceDatabase::GetResourceInfo ( skyULong a_ulHashFile, sResourceInfo* a_sResourceInfo )
{
	m_csSecureMap->VLock();
	std::map<skyULong, sResourceInfo>::iterator it;
	it = m_mapResources.find(a_ulHashFile);
	
	if(it == m_mapResources.end())
		return SKY_NOT_FOUND;

	// return the information! finally :)
	sResourceInfo& sInfo = m_mapResources[a_ulHashFile];
	a_sResourceInfo->m_bSuccess = sInfo.m_bSuccess;
	a_sResourceInfo->m_strFileExtension = sInfo.m_strFileExtension;
	a_sResourceInfo->m_strFileName = sInfo.m_strFileName;
	a_sResourceInfo->m_strFilePath = sInfo.m_strFilePath;
	a_sResourceInfo->m_strType = sInfo.m_strType;
	a_sResourceInfo->m_u32DateTimeCompiled = sInfo.m_u32DateTimeCompiled;
	a_sResourceInfo->m_u32DateTimeRaw = sInfo.m_u32DateTimeRaw;
	a_sResourceInfo->m_u32FileSizeCompiled = sInfo.m_u32FileSizeCompiled;
	a_sResourceInfo->m_u32FileSizeRaw = sInfo.m_u32FileSizeRaw;
	a_sResourceInfo->m_ulHash = sInfo.m_ulHash;
	m_csSecureMap->VUnlock();

	return SKY_OK;
}
