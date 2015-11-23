#include "stdafx.h"
#include "skyResourceManagerInstance.h"
#include "skyResourceManager.h"

static skyResourceManagerInstance g_ResManagerInstance;

skyResult skyResourceManager::Initialize(skyUInt a_u32Size)
{
	return g_ResManagerInstance.Initialize(a_u32Size);
}

skyResult skyResourceManager::Shutdown()
{
	return g_ResManagerInstance.Shutdown();
}

skyResult skyResourceManager::Load ( skyString a_strFile, skyIResource** a_pResource )
{
	return g_ResManagerInstance.Load(a_strFile, a_pResource);
}

skyResult skyResourceManager::Request ( skyIResource* a_pResource, eResourceRequestMode a_eMode )
{
	return g_ResManagerInstance.Request(a_pResource, a_eMode);
}

skyResult skyResourceManager::CacheOut ( skyIResource* a_pResource )
{
	return g_ResManagerInstance.CacheOut(a_pResource);
}

skyResult skyResourceManager::Create ( sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource  )
{
	return g_ResManagerInstance.Create(a_sDesc, a_pResource);
}