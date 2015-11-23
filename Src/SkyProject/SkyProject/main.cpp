#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include "inc_game.h"

#if defined(SKY_BUILD_DEBUG)
#pragma comment(lib, "Game_D.lib")
#else
#pragma comment(lib, "Game.lib")
#endif

	
#include <windows.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;


int main()
//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
 //                   LPSTR lpCmdLine, int nCmdShow)
{
	int i = 0;

	g_gameApplication = SKY_NEW GameApplication();

	if ( skyFailed(g_gameApplication->VInitialize ()) )
	{
		SKY_PRINT_CONSOLE("Game", "Couldn't initialize game application for further details see console or log file.", 0x0F);
		g_gameApplication->VDispose();
		SKY_SAFE_DELETE(g_gameApplication);
		std::cin >> i;
		return 1;
	}
	
	/*skyPlatformFile file(skyToString(skyConfig::g_assetDirectory) + skyToString("file.txt"), skyFileSystem::MODE_WRITE, true);
	char* string3 = "blablalbalblablalbaa";

	skySharedAsyncFileOperation pOperation = file.WriteAsync(string3, strlen(string3));
	size_t size = pOperation->WaitUntilFinished();*/


	g_gameApplication->VLoad();

	if ( skyFailed(g_gameApplication->VRun()) )
	{
		SKY_PRINT_CONSOLE("Game", "can't run game for further details see console or log file.", 0x0F);
		//skyGameInstance->VDispose();
		SKY_SAFE_DELETE(g_gameApplication);
		std::cin >> i;
		return 1;
	}

	if ( skyFailed(g_gameApplication->VDispose()) )
	{
		SKY_PRINT_CONSOLE("Game", "couldn't dispose resources for further details see console or log file.", 0x0F);
		SKY_SAFE_DELETE(g_gameApplication);
		std::cin >> i;

		return 1;
	}

	// delete instance of the game instance!
	SKY_SAFE_DELETE(g_gameApplication);

	//-----------------------------------------------------------------------------
	//  Memory Leak Checking!
	//-----------------------------------------------------------------------------
	// Set up checks for memory leaks.
    // Game Coding Complete reference - Chapter 21, page 834
    // Only activate this when we are within the debug build!
	#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();

    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	
	#endif
	
	return 0;
}