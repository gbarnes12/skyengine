#pragma once

typedef struct sGameObjectPrefabResourceCreateDesc : public sIResourceCreateDesc
{
	skyUInt m_u32Id;
	skyString m_strType;
} sGameObjectPrefabResourceCreateDesc;

class skyGameObjectPrefabUtils
{
public:
	static skyResult skyGameObjectPrefabUtils::Load(skyString a_strName, skyGameObjectPrefabResource** a_pResource);
	static skyResult skyGameObjectPrefabUtils::Request( skyGameObjectPrefabResource* a_pResource, eResourceRequestMode a_eRequestMode);
	static skyResult skyGameObjectPrefabUtils::Create( skyGameObjectPrefabResource** a_pResource );
};