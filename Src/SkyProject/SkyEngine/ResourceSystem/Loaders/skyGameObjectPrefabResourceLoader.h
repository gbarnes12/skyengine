#pragma once

class skyGameObjectPrefabResourceLoader : public skyResourceLoader
{
public:
	skyGameObjectPrefabResourceLoader::skyGameObjectPrefabResourceLoader();
public:
	virtual skyResult skyGameObjectPrefabResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyGameObjectPrefabResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyGameObjectPrefabResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyGameObjectPrefabResourceLoader::GetType() const
	{
		return "Prefab";
	}

	virtual skyBool skyGameObjectPrefabResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyGameObjectPrefabResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};