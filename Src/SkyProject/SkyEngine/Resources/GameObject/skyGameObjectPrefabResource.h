#pragma once

class skyGameObjectPrefabResource : public skyResource
{
public:
	SKY_PROPERTY_GET(skyGameObject*, m_pInstance, Instance);

	// Spawn
public:
	static skyResult skyGameObjectPrefabResource::Spawn ( sResourceInfo& a_sInfo, skyGameObjectPrefabResource** a_ppGameObject );
	static skyResult skyGameObjectPrefabResource::Spawn (sIResourceCreateDesc* a_sDesc, skyGameObjectPrefabResource** a_ppGameObject );

	//Destructor
public:
	virtual skyGameObjectPrefabResource::~skyGameObjectPrefabResource();
	// Resource Interface
public:
	virtual skyResult skyGameObjectPrefabResource::OnRequestRawData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyGameObjectPrefabResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob);
	virtual skyResult skyGameObjectPrefabResource::OnCacheOut ();
private:
	skyGameObject* m_pInstance;

	skyGameObjectPrefabResource::skyGameObjectPrefabResource (  );
};

typedef skyGameObjectPrefabResource skyGameObjectPrefab; 