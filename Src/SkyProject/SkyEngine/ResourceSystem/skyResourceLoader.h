#pragma once

class skyResourceLoader : public skyIResourceLoader
{
public:
	virtual skyResult skyResourceLoader::OnCacheOut(skyIResource* a_pResource);
	virtual skyResult skyResourceLoader::OnRequestRawData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob);
	virtual skyResult skyResourceLoader::OnRequestCompiledData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob);
};