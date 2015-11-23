#pragma once

template<class T>
class skyConfig
{
public:
	skyConfig::skyConfig(skyString a_strPath, T a_DefaultValue)
	{
		m_strPath = a_strPath;

		if(!skyConfigManager::Instance().DoesPathExist(a_strPath))
			skyConfigManager::Instance().SetValue(a_DefaultValue);

		m_tValue = skyConfigManager::Instance().GetValue(a_strPath, a_DefaultValue);
	}

	T& skyConfig::operator= (T const& a_Value)
	{
	  if (this != &a_Value)
	  {
			skyConfigManager::Instance().SetValue(m_strPath, a_Value);
			m_tValue = a_Value;
	  }

	  return *this; //Referenz auf das Objekt selbst zurückgeben
	}

private:
	skyString m_strPath;
	T m_tValue;
};