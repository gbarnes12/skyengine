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
// Name : skyApplicationSettings.cpp                                         //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Common Engine configuration structure. This struct takes a				 //
/// json file if you want to save more custom data add						 //
///	it to this struct														 //
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
#include "skyApplicationSettings.h"

///////////////////////////////////////////////////////////////////////////////
// skyApplicationSettings Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : Load (Function)
/// <summary>
/// Loads a json file with JsonCPP and parses it thus its compatible with 
/// the GameOptions structure. Returns either SKY_OK or SKY_ERROR.
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyApplicationSettings::Load(std::string gameOptionFilePath)
{

	//-----------------------------------------------------------------------------
	//  Parse the JSON File
	//-----------------------------------------------------------------------------
	/*skySharedJSONFile pFile;
	pFile = g_gameApplication->LoadResource<skyJSONFile>(gameOptionFilePath, false);

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
	return SKY_OK;*/
	return SKY_OK;
}
