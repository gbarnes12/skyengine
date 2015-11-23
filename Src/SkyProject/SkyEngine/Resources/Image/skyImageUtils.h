#pragma once

typedef struct sImageResourceCreateDesc : public sIResourceCreateDesc
{
	sGfxTextureDesc m_sTextureDesc;
} sImageResourceCreateDesc;

class skyImageUtils
{
public:
	static skyResult skyImageUtils::Load(skyString a_strName, skyImageResource** a_pResource);
	static skyResult skyImageUtils::Request(skyImageResource* a_pResource, eResourceRequestMode a_eRequestMode);
	static skyResult skyImageUtils::Create( sGfxTextureDesc& a_sDesc, skyImageResource** a_pResource);
};