#include "stdafx.h"
#include "skyGameObjectPrefabResource.h"


skyResult skyGameObjectPrefabResource::Spawn ( sResourceInfo& a_sInfo, skyGameObjectPrefabResource** a_ppGameObject )
{
	skyGameObjectPrefabResource* pResource = SKY_NEW skyGameObjectPrefabResource();
	pResource->AttachResourceInfo(a_sInfo);
	*a_ppGameObject = pResource;

	return SKY_OK;
}

skyResult skyGameObjectPrefabResource::Spawn ( sIResourceCreateDesc* a_sDesc, skyGameObjectPrefabResource** a_ppGameObject )
{
	skyGameObjectPrefabResource* pResource = SKY_NEW skyGameObjectPrefabResource();
	*a_ppGameObject = pResource;

	return SKY_OK;
}

//---------------------------------------------------------------------------------------------------------------------
skyGameObjectPrefabResource::skyGameObjectPrefabResource ( )
	: m_pInstance(NULL)
{
}

//---------------------------------------------------------------------------------------------------------------------
skyGameObjectPrefabResource::~skyGameObjectPrefabResource()
{
	OnCacheOut();
}

//---------------------------------------------------------------------------------------------------------------------
skyResult skyGameObjectPrefabResource::OnRequestRawData(sIOMemBlob& a_rMemBlob)
{
	skyAnsiStr pContent = skyGetDataFromBlob<skyAnsiStr>(a_rMemBlob);
	if(!pContent)
		return SKY_ERROR;

	rapidjson::Document mDocument;
    mDocument.Parse<0>(pContent);

	if(mDocument.HasParseError())
	{
		SKY_PRINT_CONSOLE("skyGameObjectPrefab", "Couldn't load prefab file [ " + this->m_sInfo.m_strFileName + " ].", 0x0F);
		SKY_WARNING(0, "skyGameObjectPrefab: Couldn't load prefab file [ " + this->m_sInfo.m_strFileName + " ].");

		return SKY_ERROR;
	}

	const rapidjson::Value& mParameter = mDocument["Parameters"];
	if(!mParameter.IsObject())
	{
		SKY_PRINT_CONSOLE("skyGameObjectPrefab", "Material[ " + this->m_sInfo.m_strFileName  + " ] has no parameter tag.", 0x0F);
		SKY_WARNING(0, "skyGameObjectPrefab: Material[ " + this->m_sInfo.m_strFileName  + " ] has no parameter tag.");

		return SKY_ERROR;
	}

	skyResult hr;
	SKY_VR(skyGameObjectManager::CreateGameObjectFromNode(mParameter, &m_pInstance));

	// add reference!
	m_pInstance->AddRef();

	return SKY_OK;
}

skyResult skyGameObjectPrefabResource::OnRequestCompiledData(sIOMemBlob& a_rMemBlob)
{
	return SKY_NOT_IMPLEMENTED;
}

skyResult skyGameObjectPrefabResource::OnCacheOut ()
{
	SKY_RELEASE(m_pInstance);
	return SKY_OK;
}