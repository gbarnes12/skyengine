#pragma once


class skyPerspectiveCamera : public skyICamera
{
public:
	static skyPerspectiveCamera* skyPerspectiveCamera::Create()
	{
		skyPerspectiveCamera* pCamera = SKY_NEW skyPerspectiveCamera();
		return pCamera;
	}


	skyPerspectiveCamera::skyPerspectiveCamera();
	virtual skyPerspectiveCamera::~skyPerspectiveCamera();
public:
	virtual skyVoid skyPerspectiveCamera::SetLookAt(const sGfxVector3& a_sLookAt);
	virtual skyVoid skyPerspectiveCamera::SetUp(const sGfxVector3& a_sUp);
	virtual skyVoid skyPerspectiveCamera::SetPosition(const sGfxVector3& a_sPosition);
	virtual skyVoid skyPerspectiveCamera::SetRotation(const sGfxVector3& a_sRotation);
	virtual skyVoid skyPerspectiveCamera::SetFOV(const skyFloat& a_fFOV);
	virtual skyVoid skyPerspectiveCamera::SetAspectRatio(const skyFloat& a_fAspectRatio);
	virtual skyVoid skyPerspectiveCamera::SetNearPlane(const skyFloat& a_fNear);
	virtual skyVoid skyPerspectiveCamera::SetFarPlane(const skyFloat& a_fFar);
public:
	virtual sGfxVector3 skyPerspectiveCamera::GetLookAt() const;
	virtual sGfxVector3 skyPerspectiveCamera::GetUp() const;
	virtual sGfxVector3 skyPerspectiveCamera::GetPosition() const;
	virtual sGfxVector3 skyPerspectiveCamera::GetRotation() const;
	virtual skyFloat skyPerspectiveCamera::GetFOV() const;
	virtual skyFloat skyPerspectiveCamera::GetAspectRatio() const;
	virtual skyFloat skyPerspectiveCamera::GetNearPlane() const;
	virtual skyFloat skyPerspectiveCamera::GetFarPlane() const;
public:
	virtual skyBool skyPerspectiveCamera::GetActive() const;
	virtual skyVoid skyPerspectiveCamera::SetActive(skyBool a_bValue);
public:
	virtual sGfxMatrix skyPerspectiveCamera::GetProjection();
	virtual sGfxMatrix skyPerspectiveCamera::GetView();
public:
	virtual skyVoid skyPerspectiveCamera::UpdateProjection();
	virtual skyVoid skyPerspectiveCamera::UpdateView();
private:
	sGfxVector3 m_sPosition;
	sGfxVector3 m_sLookAt;
	sGfxVector3 m_sUp;
	sGfxVector3 m_sRotation;
	skyFloat m_fFOV;
	skyFloat m_fAspectRatio;
	skyFloat m_fNear;
	skyFloat m_fFar;
	skyBool m_bIsActive;

	skyMatrix m_sProjection;
	skyMatrix m_sView;
};