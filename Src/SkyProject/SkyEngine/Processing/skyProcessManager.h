#pragma once

typedef std::vector<skyIProcessible*> skyProcessibleList; 

class skyProcessManager : public skySingleton<skyProcessManager> 
{
public:
	skyVoid skyProcessManager::Register ( skyIProcessible* a_pProcess ); 
	skyVoid skyProcessManager::Unregister ( const skyIProcessible* a_pProcess );
	skyVoid skyProcessManager::Process ( skyVoid );
private:
	skyProcessibleList m_arrProcessibles;
};