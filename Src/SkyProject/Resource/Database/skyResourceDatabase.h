#pragma once

#include "inc_resource_types.h"

typedef std::map<skyULong, sResourceInfo> skyResourceInfoMap;
class skyResourceDatabase 
{
public:
	skyResult skyResourceDatabase::Initialize ( skyResourceSystem* a_pSystem );
	skyResult skyResourceDatabase::Shutdown ( );
	skyResult skyResourceDatabase::GetResourceInfo ( skyULong a_ulHashFile, sResourceInfo* a_sResourceInfo ) ;

private:
	
	skyICriticalSection* m_csSecureMap;
	skyResourceInfoMap m_mapResources;
	skyResourceSystem* m_pSystem;
	skyWString m_strDataDir;
	skyWString m_strCompiledDir;
	skyWString m_strRawDir;

	skyVoid skyResourceDatabase::InitializeDirs();
	skyResult skyResourceDatabase::ScanRawDirectory() ;
	skyResult skyResourceDatabase::LoadDatabaseFiles ( );
	skyResult skyResourceDatabase::SearchRawFiles ( );
	skyString skyResourceDatabase::GetTypeFromExtension(std::string const& a_strExtension);
	skyResult skyResourceDatabase::SaveDatabaseFiles ( );
};