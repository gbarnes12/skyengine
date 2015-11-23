#pragma once

typedef std::map<skyGameObjectComponentId, skyIGameObjectComponent*> skyGameObjectComponentsMap;
typedef std::map<skyGameObjectId, skyGameObject*> skyGameObjectsMap;

class skyGameObject : public skyRefBaseClass
{
	// Properties
public:
	SKY_PROPERTY_GET(skyGameObjectId, m_u32Id, Id);
	SKY_PROPERTY_GET(skyGameObjectType, m_strType, Type);
	SKY_PROPERTY_GETSET(skyBool, m_bIsActive, IsActive);

	// Spawn
public:
	static skyResult skyGameObject::Spawn ( skyGameObjectId a_u32Id, skyGameObjectType a_strType, skyGameObject** a_ppGameObject );

	//Destructor
public:
	skyGameObject::~skyGameObject();

	// GameObjectComponent
public:
	template <class ComponentType>
    skyResult GetComponent(skyGameObjectComponentId a_u32ComponentId, ComponentType** a_ppComponent)
	{
		skyGameObjectComponentsMap::iterator findIt = m_mapComponents.find(a_u32ComponentId);
        if (findIt != m_mapComponents.end())
        {
			skyIGameObjectComponent* pBase = findIt->second;
			ComponentType* pDerived = static_cast<ComponentType*>(pBase);  // cast to subclass version of the pointer
			
			if(!pDerived)
				return SKY_INVALID_POINTER;
			
			*a_ppComponent = pDerived;

            return SKY_OK;  // return the weak pointer
        }
       
		return SKY_NOT_FOUND;
	};

    template <class ComponentType>
    skyResult GetComponent(skyString a_strName, ComponentType** a_ppComponent)
	{
		skyGameObjectComponentId u32Id = skyGameObjectComponent::GetIdFromName(a_strName);

		skyGameObjectComponentsMap::iterator findIt = m_mapComponents.find(u32Id);
        if (findIt != m_mapComponents.end())
        {
			skyIGameObjectComponent* pBase = findIt->second;
			ComponentType* pDerived = static_cast<ComponentType*>(pBase);  // cast to subclass version of the pointer
			
			if(!pDerived)
				return SKY_INVALID_POINTER;
			
			*a_ppComponent = pDerived;

            return SKY_OK;  // return the weak pointer
        }
       
		return SKY_NOT_FOUND;
	};

	// GameObjectComponent
public:
	void skyGameObject::AddComponent(skyIGameObjectComponent* a_pComponent);

	//Game Object
public:
	skyResult skyGameObject::AddChild( skyGameObject* a_pObject );
	skyResult skyGameObject::GetChildById( skyGameObjectId a_u32Id, skyGameObject** a_ppObject );
	skyResult skyGameObject::GetChildByType( skyGameObjectType a_strType, skyGameObject** a_ppObject );
public:
	void skyGameObject::PostInit ( );
	void skyGameObject::Update ( skyFloat a_fDeltaMS );

private:
	skyGameObjectId m_u32Id;
	skyGameObjectType m_strType;
	skyGameObjectComponentsMap m_mapComponents;
	skyGameObjectsMap m_mapChildren;
	skyBool m_bIsActive;

	skyGameObject::skyGameObject ( skyGameObjectId a_u32Id, skyGameObjectType a_strType );
};