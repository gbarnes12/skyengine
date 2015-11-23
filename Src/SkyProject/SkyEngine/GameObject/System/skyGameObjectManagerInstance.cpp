#include "stdafx.h"
#include "..\Module\skyGameObjectModule.h"
#include "skyGameObjectManagerInstance.h"


skyResult skyGameObjectManagerInstance::Initialize()
{
	//SKY_ENSURE_MODULE(skyGameObjectModule);
	// register all the components at the factory (obvious!)
	this->m_ComponentFactory.Register<skyTransformComponent> ( skyIGameObjectComponent::GetIdFromName(skyTransformComponent::m_strName) );

	m_u32LastId = 0;

	return SKY_OK;
}

skyResult skyGameObjectManagerInstance::Shutdown()
{
	for (skyGameObjectsMap::iterator it = m_mapGameObjects.begin(); it != m_mapGameObjects.end(); ++it) 
	{
		SKY_RELEASE(it->second);
	}


	return SKY_OK;
}

skyResult skyGameObjectManagerInstance::CreateGameObject ( skyGameObjectType a_strType, skyGameObject** a_ppObject )
{
	skyResult hr;
	m_u32LastId++;
	SKY_VR_FAIL(skyGameObject::Spawn(m_u32LastId, a_strType, a_ppObject));
	m_mapGameObjects.insert(std::make_pair(m_u32LastId, (*a_ppObject)));

	return hr;
FAILED:
	m_u32LastId--;
	return SKY_ERROR;
}

skyResult skyGameObjectManagerInstance::CreateGameObjectFromNode ( const rapidjson::Value& a_Node, skyGameObject** a_ppObject )
{
	skyResult hr;
	m_u32LastId++;
	skyString strType = a_Node["Type"].GetString();

	SKY_VR_FAIL(skyGameObject::Spawn(m_u32LastId, strType, a_ppObject));
	m_mapGameObjects.insert(std::make_pair(m_u32LastId, (*a_ppObject)));
	
	return SKY_OK;
FAILED:
	m_u32LastId--;
	return SKY_ERROR;
}

skyVoid skyGameObjectManagerInstance::Update(skyFloat a_fDeltaMs)
{
	for (skyGameObjectsMap::iterator it = m_mapGameObjects.begin(); it != m_mapGameObjects.end(); ++it) 
		it->second->Update(a_fDeltaMs);
}