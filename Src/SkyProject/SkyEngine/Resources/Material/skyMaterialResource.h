#pragma once

struct sGfxMaterialBuffer
{
	skyColor m_sAmbientColor;
	skyColor m_sDiffuseColor;
	skyColor m_sSpecularColor;
	
	skyFloat m_fDiffuseIntensity;
	skyFloat m_fAmbientIntensity;
	skyFloat m_fSpecularIntensity;
	
	skyUInt m_u32Shinieness;
};


class skyMaterialResource : public skyResource 
{
	friend class skyMaterialUtils;
	friend class skyMaterialResourceLoader;
public:
	SKY_PROPERTY_GETSET(skyString, m_strFileName, Name);

	SKY_PROPERTY_GET(skyImageResource*, m_pDiffuseTexture, DiffuseTexture);
	SKY_PROPERTY_GETSET(skyColor, m_sDiffuseColor, DiffuseColor);
	SKY_PROPERTY_GETSET(skyFloat, m_fDiffuseIntensity, DiffuseIntensity);

	SKY_PROPERTY_GETSET(skyColor, m_sSpecularColor, SpecularColor);
	SKY_PROPERTY_GETSET(skyFloat, m_fSpecularIntensity, SpecularIntensity);
	SKY_PROPERTY_GETSET(skyUInt, m_u32Shinieness, Shinieness);

	SKY_PROPERTY_GETSET(skyColor, m_sAmbientColor, AmbientColor);
	SKY_PROPERTY_GETSET(skyFloat, m_fAmbientIntensity, AmbientIntensity);

public:
	static skyResult skyMaterialResource::Spawn (sResourceInfo& a_sInfo, skyMaterialResource** a_pResource);
	static skyResult skyMaterialResource::Spawn (skyMaterialResource** a_pResource);

public:
	virtual skyMaterialResource::~skyMaterialResource();

public:
	virtual skyResult skyMaterialResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyMaterialResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyMaterialResource::OnCacheOut ();

public:
	skyVoid skyMaterialResource::SetDiffuseTexture(skyImageResource* a_pResource);
	skyVoid skyMaterialResource::Modify ( const rapidjson::Value& a_Data );
	skyVoid skyMaterialResource::Apply ( skyEffectResource* a_pEffect );
	// General
private:
	skyString m_strFileName;
	skyString m_strDiffuseTextureFileName;

	// Diffuse
private:
	skyFloat m_fDiffuseIntensity;
	skyColor m_sDiffuseColor;
	skyImageResource* m_pDiffuseTexture;

	// Specular
private:	
	skyColor m_sSpecularColor;
	skyFloat m_fSpecularIntensity;
	skyUInt m_u32Shinieness;

	// Ambient
private:	
	skyColor m_sAmbientColor;
	skyFloat m_fAmbientIntensity;

private:
	skyIGfxConstantBuffer* m_pPerObject;

	skyMaterialResource::skyMaterialResource()
		: m_pDiffuseTexture (nullptr)
		, m_pPerObject (nullptr)
		, m_fDiffuseIntensity(0.0f)
		, m_sDiffuseColor(1.0f, 1.0f, 1.0f)
		, m_sSpecularColor(1.0f, 1.0f, 1.0f)
		, m_fSpecularIntensity(0.0f)
		, m_u32Shinieness(0)
		, m_sAmbientColor(1.0f, 1.0f, 1.0f)
		, m_fAmbientIntensity(0.0f)
	{
	}
};