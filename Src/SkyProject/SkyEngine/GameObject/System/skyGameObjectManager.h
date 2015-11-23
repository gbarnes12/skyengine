#pragma once

class skyGameObjectManager 
{
public:
	static skyResult skyGameObjectManager::Initialize();
	static skyResult skyGameObjectManager::Shutdown();
	static skyVoid skyGameObjectManager::Update(skyFloat a_fDeltaMs);
public:
	static skyResult skyGameObjectManager::CreateGameObject ( skyGameObjectType a_strType, skyGameObject** a_ppObject );
	static skyResult skyGameObjectManager::CreateGameObjectFromNode ( const rapidjson::Value& a_Node, skyGameObject** a_ppObject );
};
