#include "stdafx.h"
#include "skyGameObjectManagerInstance.h"
#include "skyGameObjectManager.h"

skyGameObjectManagerInstance m_Instance;

skyResult skyGameObjectManager::Initialize()
{
	return m_Instance.Initialize();
}

skyResult skyGameObjectManager::Shutdown()
{
	return m_Instance.Shutdown();
}

skyVoid skyGameObjectManager::Update(skyFloat a_fDeltaMs)
{
	return m_Instance.Update(a_fDeltaMs);
}

skyResult skyGameObjectManager::CreateGameObject ( skyGameObjectType a_strType, skyGameObject** a_ppObject )
{
	return m_Instance.CreateGameObject(a_strType, a_ppObject);
}

skyResult skyGameObjectManager::CreateGameObjectFromNode ( const rapidjson::Value& a_Node, skyGameObject** a_ppObject )
{
	return m_Instance.CreateGameObjectFromNode(a_Node, a_ppObject);
}