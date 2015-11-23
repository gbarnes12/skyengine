#include "stdafx.h"
#include "skyPerspectiveCamera.h"


skyPerspectiveCamera::skyPerspectiveCamera()
	: m_sPosition(0.0f, 0.0f, 0.0f)
	, m_sLookAt(0.0f, 0.0f, 1.0f)
	, m_sUp(0.0f, 1.0f, 0.0f)
	, m_fNear(1.0f)
	, m_fFar(100.0f)
	, m_fFOV((float)D3DXToRadian(45))
	, m_bIsActive(SKY_TRUE)
{
}

skyPerspectiveCamera::~skyPerspectiveCamera()
{
}

//------------------------------------------------------------------------

skyVoid skyPerspectiveCamera::SetPosition(const sGfxVector3& a_sPosition)
{
	this->m_sPosition = a_sPosition;
}

skyVoid skyPerspectiveCamera::SetLookAt(const sGfxVector3& a_sLookAt)
{
	this->m_sLookAt = a_sLookAt;
}

skyVoid skyPerspectiveCamera::SetUp(const sGfxVector3& a_sUp)
{
	this->m_sUp = a_sUp;
}

skyVoid skyPerspectiveCamera::SetRotation(const sGfxVector3& a_sRotation)
{
	this->m_sRotation = a_sRotation;
}

skyVoid skyPerspectiveCamera::SetFOV(const skyFloat& a_fFOV)
{
	this->m_fFOV = a_fFOV;
}

skyVoid skyPerspectiveCamera::SetAspectRatio(const skyFloat& a_fAspectRatio)
{
	this->m_fAspectRatio = a_fAspectRatio;
}

skyVoid skyPerspectiveCamera::SetNearPlane(const skyFloat& a_fNear)
{
	this->m_fNear = a_fNear;
}

skyVoid skyPerspectiveCamera::SetFarPlane(const skyFloat& a_fFar)
{
	this->m_fFar = a_fFar;
}

skyVoid skyPerspectiveCamera::SetActive(skyBool a_bValue)
{
	this->m_bIsActive = a_bValue;
}

//-------------------------------------------------------------------------------------
sGfxVector3 skyPerspectiveCamera::GetPosition() const
{
	return this->m_sPosition;
}

sGfxVector3 skyPerspectiveCamera::GetRotation() const
{
	return this->m_sRotation;
}

skyFloat skyPerspectiveCamera::GetFOV() const
{
	return this->m_fFOV;
}

skyFloat skyPerspectiveCamera::GetAspectRatio() const
{
	return this->m_fAspectRatio;
}

skyFloat skyPerspectiveCamera::GetNearPlane() const
{
	return this->m_fNear;
}

skyFloat skyPerspectiveCamera::GetFarPlane() const
{
	return this->m_fFar;
}

sGfxVector3 skyPerspectiveCamera::GetLookAt() const
{
	return this->m_sLookAt;
}

sGfxVector3 skyPerspectiveCamera::GetUp() const
{
	return this->m_sUp;
}


skyBool skyPerspectiveCamera::GetActive() const
{
	return m_bIsActive;
}

//-------------------------------------------------------------------------------------

sGfxMatrix skyPerspectiveCamera::GetProjection()
{
	return this->m_sProjection;
}

sGfxMatrix skyPerspectiveCamera::GetView()
{
	return this->m_sView;
}

//-------------------------------------------------------------------------------------

skyVoid skyPerspectiveCamera::UpdateProjection()
{
	this->m_sProjection = Math::Matrix::CreatePerspectiveFieldOfView(this->m_fFOV, this->m_fAspectRatio, this->m_fNear, this->m_fFar);
}

skyVoid skyPerspectiveCamera::UpdateView()
{
	this->m_sView = Math::Matrix::CreateLookAt(this->m_sPosition, this->m_sLookAt, this->m_sUp);
}
