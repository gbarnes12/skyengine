#pragma once



class skyImageResourceLoader : public skyResourceLoader
{
public:
	skyImageResourceLoader::skyImageResourceLoader();
public:
	virtual skyResult skyImageResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyImageResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyImageResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyImageResourceLoader::GetType() const
	{
		return "Image";
	}

	virtual skyBool skyImageResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyImageResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};