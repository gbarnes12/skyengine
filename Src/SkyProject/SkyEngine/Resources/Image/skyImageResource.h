#pragma once

struct sImageResourceCreateDesc;
class skyResource;
class skyIGfxTexture;
struct sGfxTextureDesc;

class skyImageResource : public skyResource 
{
	friend class skyImageUtils;
	friend class skyImageResourceLoader;
public:
	SKY_PROPERTY_GET(skyUInt, m_u32Width, Width);
	SKY_PROPERTY_GET(skyUInt, m_u32Height, Height);
	SKY_PROPERTY_GET(skyIGfxTexture*, m_pInstance, Texture);

	static skyResult skyImageResource::Spawn (sResourceInfo& a_sInfo, skyImageResource** a_pResource);
	static skyResult skyImageResource::Spawn (sIResourceCreateDesc* a_sDesc, skyImageResource** a_pResource);

public:
	virtual skyImageResource::~skyImageResource();

public:
	virtual skyResult skyImageResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyImageResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyImageResource::OnCacheOut ();

private:
	skyIGfxTexture* m_pInstance;
	sGfxTextureDesc m_sDesc;
	skyUInt m_u32Width;
	skyUInt m_u32Height;

	skyImageResource::skyImageResource()
	 : m_pInstance(nullptr) 
	{
		SKY_ZERO_MEM(&m_sDesc, sizeof(sGfxTextureDesc));
	}

	skyVoid skyImageResource::SetFilename(skyString a_strFilename)
	{
		this->m_sDesc.m_sFileName = a_strFilename;
	}

	skyResult skyImageResource::CreateTexture();
};