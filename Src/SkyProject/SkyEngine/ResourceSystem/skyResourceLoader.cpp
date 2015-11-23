#include "stdafx.h"
#include "skyResourceLoader.h"

skyResult skyResourceLoader::OnCacheOut(skyIResource* a_pResource)
{
	if(!a_pResource)
		return SKY_INVALID_POINTER;

	return a_pResource->OnCacheOut();
}

skyResult skyResourceLoader::OnRequestRawData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob)
{
	if(!a_pResource)
		return SKY_INVALID_POINTER;

	return a_pResource->OnRequestRawData(a_rMemBlob);
}

skyResult skyResourceLoader::OnRequestCompiledData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob)
{
	if(!a_pResource)
		return SKY_INVALID_POINTER;

	return a_pResource->OnRequestCompiledData(a_rMemBlob);
}