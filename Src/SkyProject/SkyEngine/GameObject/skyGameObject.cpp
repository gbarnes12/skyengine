#include "stdafx.h"
#include "skyGameObject.h"


skyResult skyGameObject::Spawn ( skyGameObjectId a_u32Id, skyGameObjectType a_strType, skyGameObject** a_ppGameObject )
{
	skyGameObject* pResource = SKY_NEW skyGameObject(a_u32Id, a_strType);
	*a_ppGameObject = pResource;

	return SKY_OK;
}


//---------------------------------------------------------------------------------------------------------------------
skyGameObject::skyGameObject ( skyGameObjectId a_u32Id, skyGameObjectType a_strType )
	: m_u32Id (a_u32Id)
	, m_strType (a_strType)
	, m_bIsActive (SKY_TRUE)
{
}

//---------------------------------------------------------------------------------------------------------------------
skyGameObject::~skyGameObject()
{
	for (skyGameObjectComponentsMap::iterator it = m_mapComponents.begin(); it != m_mapComponents.end(); ++it)
		(it->second)->Release();

	m_mapComponents.clear();
	
	// Release all the child elements!
	for (skyGameObjectsMap::iterator it = m_mapChildren.begin(); it != m_mapChildren.end(); ++it) 
	{
		skyGameObject* pObject = it->second;
		SKY_RELEASE(pObject);
	}

	m_mapChildren.clear();
}

//---------------------------------------------------------------------------------------------------------------------
void skyGameObject::AddComponent(skyIGameObjectComponent* a_pComponent)
{
	std::pair<skyGameObjectComponentsMap::iterator, bool> success = m_mapComponents.insert(std::make_pair(a_pComponent->GetId(), a_pComponent));
	a_pComponent->AddRef();
	a_pComponent->SetOwner(this);
	//assert(success.second);
}

//---------------------------------------------------------------------------------------------------------------------
skyResult skyGameObject::AddChild( skyGameObject* a_pObject )
{
	if(!a_pObject)
		return SKY_INVALID_POINTER;

	skyGameObjectsMap::iterator findIt = m_mapChildren.find(a_pObject->GetId());
    if (findIt == m_mapChildren.end())
    {
		std::pair<skyGameObjectsMap::iterator, bool> success = m_mapChildren.insert(std::make_pair(a_pObject->GetId(), a_pObject));
		a_pObject->AddRef();
		return SKY_OK;
	}

	return SKY_ALREADY_EXISTS;
}

skyResult skyGameObject::GetChildById( skyGameObjectId a_u32Id, skyGameObject** a_ppObject )
{
	*a_ppObject = NULL;

	skyGameObjectsMap::iterator findIt = m_mapChildren.find(a_u32Id);
    if (findIt != m_mapChildren.end())
    {
		*a_ppObject = findIt->second;

        return SKY_OK;  // return the weak pointer
	}

	return SKY_NOT_FOUND;
}

skyResult skyGameObject::GetChildByType( skyGameObjectType a_strType, skyGameObject** a_ppObject )
{
	*a_ppObject = NULL;

	for (skyGameObjectsMap::iterator it = m_mapChildren.begin(); it != m_mapChildren.end(); ++it)
    {
		if((it->second)->GetType() == a_strType)
		{
			*a_ppObject = (it->second);
			return SKY_OK;
		}
    }

	return SKY_NOT_FOUND;
}

//---------------------------------------------------------------------------------------------------------------------
void skyGameObject::PostInit()
{
	for (skyGameObjectComponentsMap::iterator it = m_mapComponents.begin(); it != m_mapComponents.end(); ++it)
    {
        (it->second)->PostInit();
    }

	// now update the children
	for (skyGameObjectsMap::iterator it = m_mapChildren.begin(); it != m_mapChildren.end(); ++it)
    {
		skyGameObject* pObject = (it->second);
		if(pObject->GetIsActive())
			pObject->PostInit();
    }
}

void skyGameObject::Update ( skyFloat a_fDeltaMS )
{
	// we update the object components first
	// afterwards we can add the game obejcts!
	for (skyGameObjectComponentsMap::iterator it = m_mapComponents.begin(); it != m_mapComponents.end(); ++it)
    {
		skyIGameObjectComponent* pObject = (it->second);
		if(pObject->GetIsActive())
			pObject->Update(a_fDeltaMS);
    }

	// now update the children
	for (skyGameObjectsMap::iterator it = m_mapChildren.begin(); it != m_mapChildren.end(); ++it)
    {
		skyGameObject* pObject = (it->second);
		if(pObject->GetIsActive())
			pObject->Update(a_fDeltaMS);
    }
}