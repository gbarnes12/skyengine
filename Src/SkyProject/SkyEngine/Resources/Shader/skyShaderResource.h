#pragma once

class skyResource;
class skyIGfxShader;
struct sGfxShaderDesc;

class skyShaderResource : public skyResource 
{
public:
	SKY_PROPERTY_GET(skyIGfxShader*, m_pInstance, Shader);

public:
	static skyResult skyShaderResource::Spawn (sResourceInfo& a_sInfo, skyShaderResource** a_pResource);
	static skyResult skyShaderResource::Spawn (sIResourceCreateDesc* a_sDesc, skyShaderResource** a_pResource);

public:
	virtual skyShaderResource::~skyShaderResource();

public:
	virtual skyResult skyShaderResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyShaderResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyShaderResource::OnCacheOut ();
	
public:
	skyVoid skyShaderResource::SetDesc(sGfxShaderDesc& a_sDesc);
	sGfxShaderDesc* skyShaderResource::GetDesc();
	
public:
	skyVoid skyShaderResource::Execute();
private:
	skyIGfxShader* m_pInstance;
	sGfxShaderDesc m_sDesc;

	skyShaderResource::skyShaderResource()
		: m_pInstance(nullptr)
	{
		SKY_ZERO_MEM(&m_sDesc, sizeof(sGfxShaderDesc));
	}
};