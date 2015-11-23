#include "stdafx.h"
#include "skyImageFilterInstance.h"
#include "skyImageFilterManager.h"

static skyImageFilterInstance m_FilterInstance;

skyResult skyImageFilterManager::Initialize()
{
	return m_FilterInstance.Initialize();
}

skyResult skyImageFilterManager::Shutdown()
{
	return m_FilterInstance.Shutdown();
}

skyVoid skyImageFilterManager::Update()
{
	m_FilterInstance.Update();
}

skyVoid skyImageFilterManager::AddFilter(skyImageFilter* a_pFilter)
{
	m_FilterInstance.AddFilter(a_pFilter);
}
