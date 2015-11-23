#include "stdafx.h"
#include "skyProcessManager.h"

bool compareProcessibles (const void * a, const void * b)
{
	return (*(skyIProcessible*)a).GetLevel() <  (*(skyIProcessible*)b).GetLevel();
}

skyVoid skyProcessManager::Register ( skyIProcessible* a_pProcess )
{
	this->m_arrProcessibles.push_back(a_pProcess);
}

skyVoid skyProcessManager::Unregister ( const skyIProcessible* a_pProcess )
{
	skyProcessibleList::iterator it = m_arrProcessibles.begin();
	skyProcessibleList::iterator itEnd = m_arrProcessibles.end();

	for(it; it != itEnd; ++it)
	{
		if((*it) == a_pProcess)
		{
			it = m_arrProcessibles.erase(it);
			break;
		}
	}
}

skyVoid skyProcessManager::Process ( skyVoid )
{
	skyProcessibleList::iterator it = m_arrProcessibles.begin();
	skyProcessibleList::iterator itEnd = m_arrProcessibles.end();

	sort(m_arrProcessibles.begin(), m_arrProcessibles.end(), compareProcessibles);

	for(it; it != itEnd; ++it)
	{
		(*it)->OnProcess();
	}
}