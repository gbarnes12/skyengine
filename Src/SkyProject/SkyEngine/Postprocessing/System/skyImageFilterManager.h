#pragma once


class skyImageFilterManager 
{
public:
	static skyResult skyImageFilterManager::Initialize();
	static skyResult skyImageFilterManager::Shutdown();
	static skyVoid skyImageFilterManager::Update();
	static skyVoid skyImageFilterManager::AddFilter(skyImageFilter* a_pFilter);
};