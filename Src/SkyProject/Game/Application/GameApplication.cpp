#include "stdafx.h"
#include "GameApplication.h"

skyResult GameApplication::VInitialize()
{
	skyResult hr;
	SKY_VR(skyApplication::VInitialize());

	/*skyComPtr<skyPerspectiveCamera> pCamera(skyPerspectiveCamera::Create());
	pCamera->SetLookAt(sGfxVector3(0.0f, 0.0f, 1.0f));
	pCamera->SetPosition(sGfxVector3(5.0f, 5.0f, -10.0f));
	pCamera->SetAspectRatio((float)skyConfig::g_windowWidth / (float)skyConfig::g_windowHeight);
	pCamera->SetUp(sGfxVector3(0.0f, 1.0f, 0.0f));
	skyCameraManager::AttachCamera(pCamera.Get());
	skyCameraManager::SetAsCurrent(0);*/

	return SKY_OK;
}
