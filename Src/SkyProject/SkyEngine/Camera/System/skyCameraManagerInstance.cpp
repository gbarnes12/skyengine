#include "stdafx.h"
#include "skyCameraManagerInstance.h"


skyResult skyCameraManagerInstance::Initialize ()
{
	m_pCurrentCamera = nullptr;
	return SKY_OK;
}

skyResult skyCameraManagerInstance::Shutdown ()
{
	for(skyCameraArray::iterator it = m_arrCameras.begin(); it != m_arrCameras.end(); it++)
		(*it)->Release();

	m_arrCameras.clear();

	return SKY_OK;
}

skyResult skyCameraManagerInstance::GetCamera ( skyInt a_iIndex, skyICamera** a_ppCamera )
{
	if(a_iIndex < m_arrCameras.size())
		return SKY_INVALID_POINTER;

	(*a_ppCamera) = m_arrCameras[a_iIndex];

	return SKY_OK;
}

skyICamera* skyCameraManagerInstance::GetCurrentCamera ( )
{
	return this->m_pCurrentCamera;
}

skyVoid skyCameraManagerInstance::AttachCamera ( skyICamera* a_pCamera )
{
	if(a_pCamera)
	{
		a_pCamera->AddRef();
		this->m_arrCameras.push_back(a_pCamera);
	}
}

skyVoid skyCameraManagerInstance::SetAsCurrent ( skyInt a_iIndex )
{
	if(a_iIndex < m_arrCameras.size())
		m_pCurrentCamera  = m_arrCameras[a_iIndex];
}

skyVoid skyCameraManagerInstance::SetAsCurrent ( skyICamera* a_pCamera )
{
	if(a_pCamera)
		m_pCurrentCamera  = a_pCamera;
}

skyVoid skyCameraManagerInstance::Update()
{
	if(m_pCurrentCamera)
	{
		m_pCurrentCamera->UpdateView();
		m_pCurrentCamera->UpdateProjection();
	}
}