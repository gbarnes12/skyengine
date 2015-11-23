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
// Name : skyGLWin32View.cpp                                                  //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
///	Implementation of a window with win32. This window creates an opengl     //
/// context, too. In order to successfully control the construction of a     //
/// window use SetWindow() method of your GameApplication class.             //
///                                                                          //
/// You can use the class as a standalone version, too. In order to do so    //
/// just create a new instance of the window and call Initialize and create  //
/// methods.                                                                 //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// Its necessary to implement further logging messages into the creation    //
/// functions.                                                               //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyWindow.h"

///////////////////////////////////////////////////////////////////////////////
// skyGLWin32View Member Definitions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//  Name : skyWindow (Constructor)
/// <summary>
/// Creates a new instance of the win32 view. 
/// </summary>
//-----------------------------------------------------------------------------
skyWindow::skyWindow()
{
	this->mInstance = NULL;
	this->mPrevInstance = NULL;
	this->mCmdLine = NULL;
	this->mCmdShow = 1;
	this->mTitle = L"SkyEngine";
	this->mIsFullscreen = false;
	this->mClassName = L"SkyEngineClassWindow";
	this->mIsInitialized = false;
	this->mIsCreated = false;
	this->mWidth = 800;
	this->mHeight = 600;
}



//-----------------------------------------------------------------------------
//  Name : VInitialize (Method)
/// <summary>
/// Initializes the Win32 Window with WNDCLASSEX and registers the window 
/// properties, but in order to create the window you need to call VCreate().
/// Method will return SKY_ERROR in case of any  error or SKY_OK in case 
/// everything was ok. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyWindow::VInitialize (std::wstring title, int width, int height, bool isFullscreen, 
										int colorBits, int depthBits, int alphaBits)
{
	this->mTitle = title;
	this->mWidth = width;
	this->mHeight = height;
	this->mIsFullscreen = isFullscreen;
	this->mColorBits = colorBits;
	this->mDepthBits = depthBits;
	this->mAlphaBits = alphaBits;

	// create the window class with necessary settings
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), 
							CS_DBLCLKS, skyWindow::WndProc,
							0, 0, 
							GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
							LoadCursor(0,IDC_ARROW), (HBRUSH) GetStockObject ( BLACK_BRUSH ),
							0, this->mClassName.c_str(), 
							LoadIcon(0,IDI_APPLICATION) 
						  };

	this->mWndClassEx = wndclass;

	// if we fail to successfully initialize the window ex class
	// please return an according error result.
	if( !RegisterClassEx( &this->mWndClassEx ) ) 
	{
		SKY_PRINT_CONSOLE("skyDXWin32View", "while creating the win32 window something went wrong! Couldn't register ClassEx. Aborting now...", 0x0D);
		SKY_FATAL_ERROR(skyLogChannel::TXT_FILE, "skyDXWin32View: while creating the win32 window something went wrong! Couldn't register ClassEx. Aborting now...");

		return SKY_ERROR;
	}

	// once everything worked we can successfully say that 
	// we initialized the window!
	mIsInitialized = true;

	SKY_PRINT_CONSOLE("skyDXWin32View", "window class ex registered and created!", 0x0D);
	SKY_INFO(skyLogChannel::TXT_FILE, "skyDXWin32View: window class ex registered and created!");

	return SKY_OK;
}

//-----------------------------------------------------------------------------
//  Name : VCreate (Method)
/// <summary>
/// Finally creates the window and the opengl context. This method returns
/// SKY_ERROR if something goes wrong. 
/// </summary>
//-----------------------------------------------------------------------------
skyResult skyWindow::VCreate (void)
{
	if(!mIsInitialized)
		return SKY_ERROR;

	this->mHWnd = CreateWindow ( mClassName.c_str(), mTitle.c_str() , WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
								CW_USEDEFAULT, CW_USEDEFAULT, mWidth, mHeight, 
								NULL, NULL, mInstance, NULL);

	// if anything went wrong we'd like to return an 
	// error thus we may be able to process it further
	if( !this->mHWnd ) 
	{
		SKY_FATAL_ERROR(skyLogChannel::TXT_FILE, "skyDXWin32View: couldn't create the actual window.");
		SKY_PRINT_CONSOLE("skyDXWin32View", "couldn't create the actual window.", 0x0D);
		return SKY_ERROR;
	}

	ShowWindow ( this->mHWnd, this->mCmdShow );
	UpdateWindow ( this->mHWnd ) ;
	mIsCreated = true;

	SKY_INFO(0, "skyDXWin32View: window shown and updated.");
	SKY_PRINT_CONSOLE("skyDXWin32View", "window shown and updated.", 0x0D);

	return SKY_OK;
}


//-----------------------------------------------------------------------------
//  Name : VPeekMessages (Method)
/// <summary>
/// Peeks all the messages and takes care of dispatching them between the 
/// system. 
/// </summary>
//-----------------------------------------------------------------------------
bool skyWindow::VPeekMessages (void)
{
	if( PeekMessage ( &this->mMSG, NULL, NULL, NULL, PM_REMOVE) ) 
	{
		if( this->mMSG.message == WM_QUIT || this->mMSG.message ==WM_CLOSE ) 
		{
			return true;
		}


		TranslateMessage( &this->mMSG );
		DispatchMessage( &this->mMSG );
	}
	 
	return false;
}


//-----------------------------------------------------------------------------
//  Name : WndProc () (Static Function)
/// <summary>
/// Handles the message pumping and takes care of successfully delivering 
/// the message to the window. 
/// </summary>
//-----------------------------------------------------------------------------
LRESULT CALLBACK skyWindow::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg ) 
	{
		case WM_SIZE: 
			{
				break;
			}
		case WM_DESTROY: 
			{
				PostQuitMessage(0);
				break;
			}
		case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
			{
				break;
			}
		case WM_CHAR:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
			{
				break;
			}
		default: 
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
	}
	
	return 0;
}

//-----------------------------------------------------------------------------
//  Name : skyGLWin32View () (Destructor)
/// <summary>
/// Takes care of successfully freeing all resources!
/// </summary>
//-----------------------------------------------------------------------------
skyWindow::~skyWindow(void)
{
	SKY_PRINT_CONSOLE("skyDXWin32View:", "destructing object..", 0x0D);
	//SKY_INFO(skyLogChannel::TXT_FILE, "skyDXWin32View: destructing object..");
}