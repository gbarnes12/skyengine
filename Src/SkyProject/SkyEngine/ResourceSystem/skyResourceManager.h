#pragma once

class skyResourceManager 
{
public:
	static skyResult skyResourceManager::Initialize(skyUInt a_u32Size);
	static skyResult skyResourceManager::Shutdown();
public:
	static skyResult skyResourceManager::Load ( skyString a_strFile, skyIResource** a_pResource );
	static skyResult skyResourceManager::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode );
	static skyResult skyResourceManager::CacheOut ( skyIResource* a_pResource );
	static skyResult skyResourceManager::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  );
};