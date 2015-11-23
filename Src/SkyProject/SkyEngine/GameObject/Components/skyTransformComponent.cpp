#include "stdafx.h"
#include "skyTransformComponent.h"

skyAnsiStr skyTransformComponent::m_strName = "TransformComponent";

//-----------------------------------------------------------------------------------------------------------------------------------
skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyTransformComponent** a_pComponent)
{
	return skyTransformComponent::Spawn(a_vPosition, skyVector3(1.0f, 1.0f, 1.0f), skyVector3(0.0f, 0.0f, 0.0f), a_pComponent);
}

skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyVector3& a_vScale, skyTransformComponent** a_pComponent)
{
	return skyTransformComponent::Spawn(a_vPosition, a_vScale, skyVector3(0.0f, 0.0f, 0.0f), a_pComponent);
}

skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyVector3& a_vScale, skyVector3& a_vRotation, skyTransformComponent** a_pComponent)
{
	*a_pComponent = NULL;

	*a_pComponent = SKY_NEW skyTransformComponent(a_vPosition, a_vScale, a_vRotation);

	return SKY_OK;
}

//-----------------------------------------------------------------------------------------------------------------------------------
skyTransformComponent::skyTransformComponent ()
	: m_vPosition(0.0f)
	, m_vScale(1.0f)
	, m_vRotation(0.0f)
{
}

skyTransformComponent::skyTransformComponent (skyVector3& a_vPosition, skyVector3& a_vScale, skyVector3& a_vRotation)
	: m_vPosition (a_vPosition)
	, m_vScale(a_vScale)
	, m_vRotation(a_vRotation)
{
}

//-----------------------------------------------------------------------------------------------------------------------------------
skyResult skyTransformComponent::PostInit ()
{
	return SKY_OK;
}

//-----------------------------------------------------------------------------------------------------------------------------------
skyVoid skyTransformComponent::Update ( skyFloat a_fDeltaMs )
{
}

//-----------------------------------------------------------------------------------------------------------------------------------
skyResult skyTransformComponent::ModifyByNode( const rapidjson::Value& a_Node )
{
	return SKY_OK;
}

