#pragma once

struct sIResourceCreateDesc
{
	skyString m_strType;
};

class skyIResource : public skyRefBaseClass
{
	friend class skyResourceSystem;
public:
	virtual skyVoid skyIResource::AttachResourceInfo(sResourceInfo a_sInfo) = 0;
	virtual sResourceInfo& skyIResource::GetInfo() = 0;
	virtual eResourceState skyIResource::GetResourceState() const = 0;

public:
	virtual skyResult skyIResource::OnRequestRawData(sIOMemBlob& a_rMemBlob) = 0;
	virtual skyResult skyIResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob) = 0;
	virtual skyResult skyIResource::OnCacheOut () = 0;
	virtual skyVoid skyIResource::SetResourceState(eResourceState a_eState) = 0;
};

class skyIResourceLoader 
{
public:
	virtual skyResult skyIResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource) = 0;
	virtual skyResult skyIResourceLoader::OnCacheOut(skyIResource* a_pResource) = 0;
	virtual skyResult skyIResourceLoader::OnRequestRawData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob) = 0;
	virtual skyResult skyIResourceLoader::OnRequestCompiledData(skyIResource* a_pResource, sIOMemBlob& a_rMemBlob) = 0;
	virtual skyResult skyIResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource) = 0;
	virtual std::vector<skyString> const& skyIResourceLoader::GetExtensions() = 0;
	virtual skyString skyIResourceLoader::GetType() const = 0;
	virtual skyBool skyIResourceLoader::IsBinary() const = 0;
	virtual skyBool skyIResourceLoader::EscapeNull() const = 0;
};