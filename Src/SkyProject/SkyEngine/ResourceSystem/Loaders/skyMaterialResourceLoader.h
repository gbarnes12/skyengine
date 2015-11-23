#pragma once

class skyMaterialResourceLoader : public skyResourceLoader
{
public:
	skyMaterialResourceLoader::skyMaterialResourceLoader();
public:
	virtual skyResult skyMaterialResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyMaterialResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyMaterialResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyMaterialResourceLoader::GetType() const
	{
		return "Material";
	}

	virtual skyBool skyMaterialResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyMaterialResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};