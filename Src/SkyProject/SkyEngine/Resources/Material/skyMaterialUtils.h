#pragma once


class skyMaterialUtils
{
public:
	static skyResult skyMaterialUtils::Load(skyString a_strName, skyMaterialResource** a_pResource);
	static skyResult skyMaterialUtils::Request(skyMaterialResource* a_pResource, eResourceRequestMode a_eRequestMode);
	static skyResult skyMaterialUtils::Create( skyMaterialResource** a_pResource );
};