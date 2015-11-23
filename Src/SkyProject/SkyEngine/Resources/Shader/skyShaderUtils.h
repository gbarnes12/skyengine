#pragma once

typedef struct sEffectResourceCreateDesc : public sIResourceCreateDesc
{
	sGfxShaderDesc* m_sPixelShaderDesc;
	sGfxShaderDesc* m_sVertexShaderDesc;
} sEffectResourceCreateDesc;

class skyShaderUtils
{
public:
	static skyResult skyShaderUtils::Load(skyString a_strName, skyShaderResource** a_pResource, sGfxShaderDesc& a_sDesc);
	static skyResult skyShaderUtils::Request(skyShaderResource* a_pResource, eResourceRequestMode a_eRequestMode);
	static skyResult skyShaderUtils::CreateEffect (sGfxShaderDesc& a_sVertexShaderDesc, sGfxShaderDesc& a_sPixelShaderDesc, skyEffectResource** a_pResource);
};