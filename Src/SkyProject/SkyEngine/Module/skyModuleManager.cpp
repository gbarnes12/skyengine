#include "stdafx.h"
#include "skyModule.h"
#include "skyModuleManager.h"

bool compareModule (const void * a, const void * b)
{
  skyModule* aModule =  (skyModule*)a;
  skyModule* bModule =  (skyModule*)b;
  return (aModule->GetLevel() < bModule->GetLevel());
}

skyModuleManager::~skyModuleManager()
{
}

skyResult skyModuleManager::Initialize()
{
	/*skyModuleList::iterator it;
	skyModuleList::iterator itBegin = m_arrModules.begin();
	skyModuleList::iterator itEnd = m_arrModules.end();
	
	std::sort(m_arrModules.begin(), m_arrModules.end(), compareModule);

	for(it = itBegin; it != itEnd; ++it)
	{
		skyResult hr;
		SKY_VR((*it)->Initialize());
	}*/

	return SKY_OK;
}

skyResult skyModuleManager::Shutdown()
{
	/*skyModuleList::iterator it;
	skyModuleList::iterator itBegin = m_arrModules.begin();
	skyModuleList::iterator itEnd = m_arrModules.end();
	sort(m_arrModules.begin(), m_arrModules.end(),  compareModule);

	for(it = itBegin; it != itEnd; it++ )
	{
		(*it)->Shutdown();
	}

	m_arrModules.clear();*/

	return SKY_OK;
}

skyVoid skyModuleManager::Register ( skyModule* a_pModule )
{
	//this->m_arrModules.push_back(a_pModule);
}
