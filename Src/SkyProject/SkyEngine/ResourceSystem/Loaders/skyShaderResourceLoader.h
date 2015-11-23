#pragma once

class skyShaderResourceLoader : public skyResourceLoader
{
public:
	skyShaderResourceLoader::skyShaderResourceLoader();
public:
	virtual skyResult skyShaderResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyShaderResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyShaderResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyShaderResourceLoader::GetType() const
	{
		return "Shader";
	}

	virtual skyBool skyShaderResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyShaderResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};