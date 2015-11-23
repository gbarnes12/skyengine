//---------------------------------------------------------------------------//
//				___________     __   ___  ___      ___                       //
//				|  _______ \   |  | /  /  \  \    /  /                       //
//				|  |           |  |/  /    \  \  /  /                        //
//				|  |_______    |     /      \  \/  /                         //
//				\_________ \   |     |       \    /                          //
//				  _		 |  |  |  |\  \       |  |                           //
//				 | \_____|  |  |  | \  \      |  |                           //
//				 |__________/  |__|  \__\     |__|  Engine.                  //
//                                                                           //
//---------------------------------------------------------------------------//
//                                                                           //
// Name : skyConfigValue.cpp												 //
// Author: Fadil		                                                     //
//                                                                           //
/// <summary>                                                                //
/// Tasks																	 //
/// 1. create and change easily config values								 //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyConfigValue.h"
#include "skyConfigManager.h"

skyConfigValue::skyConfigValue(eConfigLayer a_eLayer, std::string a_strPath,  rapidjson::Type a_tValue, rapidjson::Type a_tDefaultValue)
{
    if(skyConfigManager::Get(a_strPath) == false) 
		skyConfigManager::GetInstance().Set(a_eLayer, a_strPath, a_strValue, a_tDefaultValue); 
	this->m_tDefaultValue = a_tDefaultValue;
}
}


skyConfigValue::skyConfigValue(void)
{
}


skyConfigValue::~skyConfigValue(void)
{
}
