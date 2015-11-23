#include "stdafx.h"
#include "..\Module\skyImageFilterModule.h"
#include "skyImageFilterInstance.h"


skyResult skyImageFilterInstance::Initialize()
{
	//SKY_ENSURE_MODULE(skyImageFilterModule);
	return SKY_OK;
}

skyResult skyImageFilterInstance::Shutdown()
{
	for(std::vector<skyImageFilter*>::iterator it = m_arrFilters.begin(); it != m_arrFilters.end(); it++)
		SKY_SAFE_DELETE((*it));

	m_arrFilters.clear();

	return SKY_OK;
}

skyVoid skyImageFilterInstance::Update()
{
	skyGfxCullingManager::Instance().ExtractObjects(m_Batch);

	for(skyUInt i = 0; i < m_arrFilters.size(); i++) {
		if(m_arrFilters[i]->GetActive())
		{
			m_arrFilters[i]->Update(&m_Batch);
		}
	}

	m_Batch.ClearObjects();
	skyGfxCullingManager::Instance().ClearObjects();
}

skyVoid skyImageFilterInstance::AddFilter(skyImageFilter* a_pFilter)
{
	assert(a_pFilter != NULL);
	m_arrFilters.push_back(a_pFilter);
}