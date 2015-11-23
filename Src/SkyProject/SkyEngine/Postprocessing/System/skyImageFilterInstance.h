#pragma once 


class skyImageFilterInstance
{
public:
	skyResult skyImageFilterInstance::Initialize();
	skyResult skyImageFilterInstance::Shutdown();
	skyVoid skyImageFilterInstance::Update();
	skyVoid skyImageFilterInstance::AddFilter(skyImageFilter* a_pFilter);

private:
	std::vector<skyImageFilter*> m_arrFilters;
	skyGfxRenderBatch m_Batch;
};