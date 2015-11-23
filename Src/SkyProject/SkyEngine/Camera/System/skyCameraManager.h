#pragma once 

class skyCameraManager
{
public:
	static skyResult skyCameraManager::Initialize ();
	static skyResult skyCameraManager::Shutdown ();
public:
	static skyVoid skyCameraManager::AttachCamera ( skyICamera* a_pCamera );
	static skyResult skyCameraManager::GetCamera ( skyInt a_iIndex, skyICamera** a_ppCamera );
	static skyICamera* skyCameraManager::GetCurrentCamera ( );
	static skyVoid skyCameraManager::SetAsCurrent ( skyInt a_iIndex );
	static skyVoid skyCameraManager::SetAsCurrent ( skyICamera* a_ppCamera );
	static skyVoid skyCameraManager::Update();
};