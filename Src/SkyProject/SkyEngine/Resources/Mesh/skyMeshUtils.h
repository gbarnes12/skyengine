#pragma once
/*
typedef struct sImageResourceCreateDesc : public sIResourceCreateDesc
{
	sGfxTextureDesc m_sTextureDesc;
} sImageResourceCreateDesc;
*/
class skyMeshUtils
{
public:
	static skyResult skyMeshUtils::Load(skyString a_strName, skyMeshResource** a_pResource);
	static skyResult skyMeshUtils::Request(skyMeshResource* a_pResource, eResourceRequestMode a_eRequestMode);
	//static skyResult skyMeshUtils::Create( sGfxTextureDesc& a_sDesc, skyMeshResource** a_pResource);
};