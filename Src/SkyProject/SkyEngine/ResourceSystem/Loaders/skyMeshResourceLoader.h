#pragma once

class skyMeshResourceLoader : public skyResourceLoader
{
public:
	skyMeshResourceLoader::skyMeshResourceLoader();
public:
	virtual skyResult skyMeshResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyMeshResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyMeshResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyMeshResourceLoader::GetType() const
	{
		return "Mesh";
	}

	virtual skyBool skyMeshResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyMeshResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};