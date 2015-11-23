#include "stdafx.h"
#include "skyConfigManager.h"

skyResult skyConfigManager::Load(skyString configFilePath)
{
	if( configFilePath.substr(configFilePath.find_last_of(".") + 1) == "conf" )
		// Load Json
		return SKY_OK;
	else if( configFilePath.substr(configFilePath.find_last_of(".") + 1) == "xml" )
		// Load XML
		return SKY_OK;
	else
		return SKY_OK;
}


skyConfigManager::~skyConfigManager(void)
{
}
