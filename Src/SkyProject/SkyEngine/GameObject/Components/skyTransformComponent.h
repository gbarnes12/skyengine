#pragma once

class skyTransformComponent : public skyGameObjectComponent 
{
public:
	static skyAnsiStr m_strName;
	SKY_PROPERTY_GETSET(skyVector3, m_vPosition, Position);
	SKY_PROPERTY_GETSET(skyVector3, m_vScale, Scale);
	SKY_PROPERTY_GETSET(skyVector3, m_vRotation, Rotation);
	// spawn methods
public:
	static skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyTransformComponent** a_pComponent);
	static skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyVector3& a_vScale, skyTransformComponent** a_pComponent);
	static skyResult skyTransformComponent::Spawn (skyVector3& a_vPosition, skyVector3& a_vScale, skyVector3& a_vRotation, skyTransformComponent** a_pComponent);
	
	skyTransformComponent::skyTransformComponent ();
public:
	virtual skyResult skyTransformComponent::ModifyByNode( const rapidjson::Value& a_Node );
	virtual skyString skyTransformComponent::GetName() const { return m_strName; }

public:
	virtual skyResult skyTransformComponent::PostInit ();
	virtual skyVoid skyTransformComponent::Update ( skyFloat a_fDeltaMs );

private:
	skyVector3 m_vPosition;
	skyVector3 m_vScale;
	skyVector3 m_vRotation;

	
	skyTransformComponent::skyTransformComponent (skyVector3& a_vPosition, skyVector3& a_vScale, skyVector3& a_vRotation);
};