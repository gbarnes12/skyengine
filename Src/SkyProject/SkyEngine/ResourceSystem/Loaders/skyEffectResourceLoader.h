#pragma once

class skyEffectResourceLoader : public skyResourceLoader
{
public:
	skyEffectResourceLoader::skyEffectResourceLoader();
public:
	virtual skyResult skyEffectResourceLoader::OnLoadIn(sResourceInfo& a_sInfo, skyIResource** a_pResource);
	virtual skyResult skyEffectResourceLoader::OnCreateResource(sIResourceCreateDesc* a_sDesc, skyIResource** a_pResource);
public:
	virtual std::vector<skyString> const& skyEffectResourceLoader::GetExtensions()
	{
		return m_arrExtensions;
	}

	virtual skyString skyEffectResourceLoader::GetType() const
	{
		return "Effect";
	}

	virtual skyBool skyEffectResourceLoader::IsBinary() const
	{
		return SKY_FALSE;
	}

	virtual skyBool skyEffectResourceLoader::EscapeNull() const
	{
		return SKY_TRUE;
	}
private:
	std::vector<skyString> m_arrExtensions;
};