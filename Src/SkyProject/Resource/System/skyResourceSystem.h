#pragma once 
#include "skyResourceCache.h"
#include "Database\skyResourceDatabase.h"

typedef std::vector<skyIResourceLoader*> skyResourceLoaderArray;
typedef std::map<skyULong, skyIResource*> skyResourceMap;
typedef std::list< skyULong > skyRecentlyUsedResourceArray; 
typedef std::vector< skyIResource* > skyCreatedResources; 


class skyResourceSystem
{
	friend class skyResourceCache;
	friend class skyResourceDatabase;
public:
	skyResult skyResourceSystem::Initialize(skyUInt a_u32Size, eResourceMode a_eMode = eResourceMode_Raw);
	skyResult skyResourceSystem::Shutdown();

	skyVoid skyResourceSystem::RegisterLoader(skyIResourceLoader* a_pLoader);
public:
	skyResult skyResourceSystem::Load ( skyString a_strFile, skyIResource** a_pResource );
	skyResult skyResourceSystem::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode );
	skyResult skyResourceSystem::CacheOut ( skyIResource* a_pResource );
	skyResult skyResourceSystem::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  );

	// File System
private:
	skyFileSystem m_FileSystem;
	skyDiskFileDevice m_DiskFileDevice;
	skyZipFileDevice m_ZipFileDevice;
	// intern stuff
private:
	skyResourceCache m_Cache;
	skyResourceDatabase m_Database;
	skyResourceLoaderArray m_arrLoaders;
	skyResourceMap m_mapResources;
	skyRecentlyUsedResourceArray m_arrRecentlyUsedResources;
	skyCreatedResources m_arrCreatedResources;
	eResourceMode m_eMode;

	skyResult skyResourceSystem::RequestImmediate ( skyIResource* a_pResource );
	skyResult skyResourceSystem::RequestDeferred ( skyIResource* a_pResource );
	skyVoid skyResourceSystem::Update ( skyIResource* a_pResource );
	skyResult skyResourceSystem::CacheOutOneResource (  );
	skyVoid skyResourceSystem::Flush ( );
	skyIResourceLoader* skyResourceSystem::FindResourceLoader (sResourceInfo* sInfo);
};