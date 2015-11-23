#pragma once

#include "inc_resource_types.h"

typedef std::map<skyULong, sResourceInfo> skyCacheMap;

class skyResourceCache
{
public:
	skyResult skyResourceCache::Initialize( skyUInt a_uiSize, skyResourceSystem* a_pInstance);
	skyResult skyResourceCache::Shutdown( );

	skyResult skyResourceCache::In (  sResourceInfo& a_sInfo, sIOMemBlob* a_pBlob, skyUInt a_u32AddSize = 0 );
	skyVoid skyResourceCache::Out (  sResourceInfo& a_sInfo );

private:
	skyResourceSystem* m_pInstance;
	skyUInt m_u32CacheSize;
	skyUInt m_u32CurrentlyAllocated;
	skyCacheMap m_mapCache;


};