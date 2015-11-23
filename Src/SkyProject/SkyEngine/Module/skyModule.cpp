#include "stdafx.h"
#include "skyModule.h"

skyModule::skyModule()
	: m_iLevel ( eModuleLevel_Default )
{
}

skyModule::~skyModule()
{
}

skyInt skyModule::GetLevel () const
{
	return m_iLevel;
}

skyVoid skyModule::SetLevel ( const skyInt a_iLevel )
{
	m_iLevel = a_iLevel;
}
	
skyResult skyModule::Initialize()
{
	return SKY_OK;
} 

skyResult skyModule::Shutdown()
{
	return SKY_OK;
}