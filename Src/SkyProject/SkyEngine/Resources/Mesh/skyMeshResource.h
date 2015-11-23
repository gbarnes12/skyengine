#pragma once

struct sImageResourceCreateDesc;
class skyResource;
class skyIGfxPrimitive;
class skyMaterialResource;

typedef std::vector<skySubmeshResource*> skySubMeshList;

class skyMeshResource : public skyResource 
{
	friend class skyMeshUtils;
	friend class skyMeshResourceLoader;
	friend class skySubmeshResource;
public:
	static skyResult skyMeshResource::Spawn (sResourceInfo& a_sInfo, skyMeshResource** a_pResource);
	static skyResult skyMeshResource::Spawn (sIResourceCreateDesc* a_sDesc, skyMeshResource** a_pResource);

public:
	virtual skyMeshResource::~skyMeshResource();

public:
	virtual skyResult skyMeshResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyMeshResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyMeshResource::OnCacheOut ();

	// Get 
//public:
	//skySubmeshResource* skyMeshResource::GetMesh(skyUInt a_u32Index) const;
	// Set
public:
	skyVoid skyMeshResource::SetMaterial ( skyUInt a_u32Index, skyMaterialResource* a_pMaterial );
	skyVoid skyMeshResource::SetMaterial ( skyMaterialResource* a_pMaterial );
	// Utils
public:
	skyVoid skyMeshResource::Draw ();

private:
	skyEffectResource* m_pEffect;
	skySubMeshList m_arrMeshes;
	skyString m_strName;

	skyMeshResource::skyMeshResource()
		: m_pEffect(nullptr)
	{
	}
};