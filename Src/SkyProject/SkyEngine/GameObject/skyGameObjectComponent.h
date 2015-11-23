#pragma once 

class skyGameObjectComponent : public skyIGameObjectComponent 
{
public:
	skyGameObjectComponent::~skyGameObjectComponent() { SKY_RELEASE(m_pOwner); }
public:
	virtual skyBool skyGameObjectComponent::GetIsActive()
	{
		return m_bIsActive;
	}

	virtual skyVoid skyGameObjectComponent::SetIsActive(skyBool a_bIsActive)
	{
		m_bIsActive = a_bIsActive;
	}

protected:
	skyGameObject* m_pOwner;
	skyBool m_bIsActive;
private:
	virtual skyVoid skyGameObjectComponent::SetOwner ( skyGameObject* a_pObject ) 
	{ 
		SKY_RELEASE(m_pOwner); 
		m_pOwner = a_pObject; 
		m_pOwner->AddRef();   
	}
};