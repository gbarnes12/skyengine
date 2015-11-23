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

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyConfigManager.h"
#include "Extern\rapidjson\document.h"
#include "Extern\rapidjson\reader.h"

using namespace std;
using namespace rapidjson;


map<string,string> configMap;

skyResult skyConfigManager::Load(string configFilePath)
{
	// First load the JSON File

	// Parse the JSON FIle

	// And save it into the Hash Map

	//Finished

	//-----------------------------------------------------------------------------
	//  Parse the JSON File
	//-----------------------------------------------------------------------------
	/*
	skySharedJSONFile pFile;
	pFile = g_gameApplication->LoadResource<skyJSONFile>(configFilePath, false);

	if(pFile)
	{
		const rapidjson::Value& jRoot = pFile->GetRoot();
		if(jRoot.IsNull())
			return SKY_ERROR;

		const rapidjson::Value& jWindowNode = jRoot["Settings"]["Window"];
		if(!jWindowNode.IsNull())
		{
			skyConfig::g_windowWidth = jWindowNode["Width"].GetInt();
			skyConfig::g_windowHeight = jWindowNode["Height"].GetInt();
			skyConfig::g_windowColorBits = jWindowNode["ColorBits"].GetInt();
			skyConfig::g_windowDepthBits = jWindowNode["DepthBits"].GetInt();
			skyConfig::g_windowAlphaBits = jWindowNode["AlphaBits"].GetInt();
			skyConfig::g_windowIsFullscreen = jWindowNode["IsFullscreen"].GetBool();
		}

		const rapidjson::Value& jRendererNode = jRoot["Settings"]["Renderer"];
		if(!jRendererNode.IsNull())
		{
			skyConfig::g_showFPS = jRendererNode["ShowFPS"].GetBool();
			skyConfig::g_deferredDebugMode = jRendererNode["DeferredDebugMode"].GetBool();

			const rapidjson::Value& jCameraNode = jRendererNode["Camera"];
			if(!jCameraNode.IsNull())
			{
				skyUInt t = 0;
				skyConfig::g_cameraPosition = skyVector3((float)jCameraNode["Position"][t].GetDouble(), 
														(float)jCameraNode["Position"][++t].GetDouble(),
														(float)jCameraNode["Position"][++t].GetDouble()
														);
				t = 0;
				skyConfig::g_cameraLookAt = skyVector3( (float)jCameraNode["LookAt"][t].GetDouble(), 
														(float)jCameraNode["LookAt"][++t].GetDouble(),
														(float)jCameraNode["LookAt"][++t].GetDouble()
														);
			}

		}

		const rapidjson::Value& jDevelopmentNode = jRoot["Settings"]["Development"];
		if(!jDevelopmentNode.IsNull())
		{
			skyConfig::g_IsDebugMode = jDevelopmentNode["IsDebugMode"].GetBool();
			skyConfig::g_assetDirectory = jDevelopmentNode["AssetDirectory"].GetString();
		}

		//-----------------------------------------------------------------------------
		// Delete Buffer again
		//-----------------------------------------------------------------------------
		SKY_PRINT_CONSOLE("skyApplicationSettings", "settings loaded successfully. You can now use them!", 0x0F);
		SKY_INFO(0, "skyApplicationSettings: settings loaded successfully. You can now use them!");
	}
	*/
	return SKY_OK;
}
skyResult skyConfigManager::AddConfig(string configFilePath)
{
	configMap.insert("/Game/Dlc1","Value");
	return SKY_OK;
}

skyResult skyConfigManager::Save()
{
	return SKY_OK;
}

skyResult skyConfigManager::Get()
{
	return SKY_OK;
}

skyResult skyConfigManager::GetInstance()
{
	return SKY_OK;
}

skyConfigManager::skyConfigManager(void)
{
}


skyConfigManager::~skyConfigManager(void)
{
}



