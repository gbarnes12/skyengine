#include "stdafx.h"
#include "skyCameraManagerInstance.h"
#include "skyCameraManager.h"

skyCameraManagerInstance m_CameraManagerInstance;

skyResult skyCameraManager::Initialize ()
{
	return m_CameraManagerInstance.Initialize();
}

skyResult skyCameraManager::Shutdown ()
{
	return m_CameraManagerInstance.Shutdown();
}


skyVoid skyCameraManager::AttachCamera ( skyICamera* a_pCamera )
{
	m_CameraManagerInstance.AttachCamera(a_pCamera);
}

skyResult skyCameraManager::GetCamera ( skyInt a_iIndex, skyICamera** a_ppCamera )
{
	return m_CameraManagerInstance.GetCamera(a_iIndex, a_ppCamera);
}

skyICamera* skyCameraManager::GetCurrentCamera ( )
{
	return m_CameraManagerInstance.GetCurrentCamera();
}

skyVoid skyCameraManager::SetAsCurrent ( skyInt a_iIndex )
{
	 m_CameraManagerInstance.SetAsCurrent(a_iIndex);
}

skyVoid skyCameraManager::SetAsCurrent ( skyICamera* a_ppCamera )
{
	 m_CameraManagerInstance.SetAsCurrent(a_ppCamera);
}

skyVoid skyCameraManager::Update()
{
	m_CameraManagerInstance.Update();
}