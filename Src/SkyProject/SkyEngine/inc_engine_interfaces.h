#pragma once

class skyIGameObjectComponent : public skyRefBaseClass
{
	friend class skyGameObject;
	friend class skyGameObjectComponentFactory;
public:
	virtual skyIGameObjectComponent::~skyIGameObjectComponent() {}
public:
	virtual skyVoid skyIGameObjectComponent::SetIsActive(skyBool a_bIsActive) = 0;
	virtual skyBool skyIGameObjectComponent::GetIsActive() = 0;
	virtual skyResult skyIGameObjectComponent::PostInit () = 0;
	virtual skyVoid skyIGameObjectComponent::Update ( skyFloat a_fDeltaMs ) = 0;
public:
	virtual skyGameObjectComponentId skyIGameObjectComponent::GetId(void) const { return GetIdFromName(GetName()); }
	virtual skyString skyIGameObjectComponent::GetName() const = 0;
public:
	virtual skyResult skyIGameObjectComponent::ModifyByNode( const rapidjson::Value& a_Node ) = 0;
	// static
public:
	static skyGameObjectComponentId skyIGameObjectComponent::GetIdFromName(skyString a_strName)
    {
		void* rawId = skyHashedString::HashName(a_strName.c_str());
        return reinterpret_cast<skyGameObjectComponentId>(rawId);
    }
private:
	virtual void skyIGameObjectComponent::SetOwner ( skyGameObject* a_pObject ) = 0;
};

class skyICamera : public skyRefBaseClass
{
public:
	virtual skyICamera::~skyICamera() {}
public:
	virtual skyVoid skyICamera::SetNearPlane(const skyFloat& a_fNear) = 0;
	virtual skyVoid skyICamera::SetFarPlane(const skyFloat& a_fFar) = 0;
public:
	virtual skyFloat skyICamera::GetNearPlane() const = 0;
	virtual skyFloat skyICamera::GetFarPlane() const = 0;
public:
	virtual skyBool skyICamera::GetActive() const = 0;
	virtual skyVoid skyICamera::SetActive(skyBool a_bValue) = 0;
public:
	virtual sGfxMatrix skyICamera::GetProjection() = 0;
	virtual sGfxMatrix skyICamera::GetView() = 0;
public:
	virtual skyVoid skyICamera::UpdateProjection() = 0;
	virtual skyVoid skyICamera::UpdateView() = 0;
};