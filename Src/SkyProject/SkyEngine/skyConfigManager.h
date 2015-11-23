
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
// Name : skyConfigManager.cpp												 //
// Author: Fadil		                                                     //
//                                                                           //
/// <summary>                                                                //
/// Tasks																	 //
/// 1. loads Config .xml oder .json File									 //
/// 2. saves values in a map with two string values							 //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
///////////////////////////////////////////////////////////////////////////////
#pragma once
class skyConfigManager : public skySingleton<skyConfigManager>
{
public:
	skyConfigManager(void);
	~skyConfigManager(void);
	static skyResult skyConfigManager::Load(string configFilePath);
	static skyResult skyConfigManager::Save();
	static skyResult skyConfigManager::Get();
	static skyResult skyConfigManager::GetInstance();
	static skyResult skyConfigManager::AddConfig(string configFilePath);
private:
	std::map<string,string> configManagerSettingsMap;
};

