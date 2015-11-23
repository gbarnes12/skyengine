#pragma once

typedef std::vector<skyModule*> skyModuleList;

class skyModuleManager : public skySingleton<skyModuleManager>
{
		friend skySingleton<skyModuleManager>; 
private:
	skyModuleManager::~skyModuleManager();
	skyModuleManager::skyModuleManager() {}
public:
	skyResult skyModuleManager::Initialize();
	skyResult skyModuleManager::Shutdown();

	skyVoid skyModuleManager::Register (  skyModule* a_rModule );

private:
	skyModuleList m_arrModules;
};