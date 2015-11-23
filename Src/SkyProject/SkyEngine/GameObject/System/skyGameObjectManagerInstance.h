#pragma once


class skyGameObjectManagerInstance 
{
public:
	skyResult skyGameObjectManagerInstance::Initialize();
	skyResult skyGameObjectManagerInstance::Shutdown();
	skyVoid skyGameObjectManagerInstance::Update(skyFloat a_fDeltaMs);
	skyResult skyGameObjectManagerInstance::CreateGameObject ( skyGameObjectType a_strType, skyGameObject** a_ppObject );
	skyResult skyGameObjectManagerInstance::CreateGameObjectFromNode ( const rapidjson::Value& a_Node, skyGameObject** a_ppObject );

private:
	skyGameObjectId m_u32LastId;
	skyGameObjectsMap m_mapGameObjects;
	skyGenericObjectFactory<skyIGameObjectComponent, skyGameObjectComponentId> m_ComponentFactory;
};