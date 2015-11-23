#pragma once

class skyConfigManager : public skySingleton<skyConfigManager>
{
public:
	~skyConfigManager(void);

public:
	skyResult skyConfigManager::Initialize();
	skyResult skyConfigManager::Shutdown();
	skyResult skyConfigManager::Load(skyString configFilePath);

public:
	skyBool skyConfigManager::DoesPathExist(skyString a_strPath);
public:
	template<class T>
	T GetValue(skyString a_strPath, T a_32DefaultValue);

public:
	template<class T>
	void SetValue(skyString a_strPath, T a_DefaultValue);

private:
	std::map<skyString, skyString> m_mapConfigs;

	template<class T>
	T CastToType(skyString a_strValue);
};

template<class T>
skyResult CastToType(skyString a_strValue, T& a_Value)
{
	if(typeid(T) == typeid(skyInt) || typeid(T) == typeid(skyUInt)) {
		a_Value = atoi(a_strValue.c_str()); 
		return SKY_OK;
	}

	if(typeid(T) == typeid(skyBool)) {
		a_Value = (a_strValue == "True" || a_strValue == "1") ? true : false; 
		return SKY_OK;
	}

	if(typeid(T) == typeid(skyFloat)) {
		a_Value = (skyFloat)atof(a_strValue.c_str());
		return SKY_OK;
	}

	if(typeid(T) == typeid(skyString)) {
		a_Value = a_strValue;
		return SKY_OK;
	}

	return SKY_INVALID_CAST;
}

template<class T>
T skyConfigManager::GetValue(skyString a_strPath, T a_32DefaultValue)
{
	if(m_mapConfigs.find(a_strPath) == m_mapConfigs.end())
		return a_32DefaultValue;

	T tValue;
	skyResult hr;

	hr = CastToType<T>(m_mapConfigs[a_strPath], tValue);
	if(hr == SKY_INVALID_CAST)
		return a_32DefaultValue;

	return tValue;
}

template<class T>
void skyConfigManager::SetValue(skyString a_strPath, T a_DefaultValue)
{
	skyString strValue = skyToString(a_DefaultValue);

	if(m_mapConfigs.find(a_strPath) == m_mapConfigs.end())
		m_mapConfigs.insert(std::pair(a_strPath, ""));

	m_mapConfigs[a_strPath] = strValue;
}