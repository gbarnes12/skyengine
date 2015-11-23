#pragma once

typedef std::vector<skyICamera*> skyCameraArray;


class skyCameraManagerInstance
{
public:
	skyResult skyCameraManagerInstance::Initialize ();
	skyResult skyCameraManagerInstance::Shutdown ();
public:
	skyVoid skyCameraManagerInstance::AttachCamera ( skyICamera* a_pCamera );
	skyResult skyCameraManagerInstance::GetCamera ( skyInt a_iIndex, skyICamera** a_ppCamera );
	skyVoid skyCameraManagerInstance::SetAsCurrent ( skyInt a_iIndex );
	skyVoid skyCameraManagerInstance::SetAsCurrent ( skyICamera* a_ppCamera );
	skyICamera* skyCameraManagerInstance::GetCurrentCamera ( );
	skyVoid skyCameraManagerInstance::Update();
private:
	skyCameraArray m_arrCameras;
	skyICamera* m_pCurrentCamera;
};