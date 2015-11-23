#pragma once
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
// Name : skyWindow.h                                                        //
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

#if  defined(WIN32) || defined(_WIN32)

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyWindow (Interface)
/// <summary>
/// Basic interface that provides necessary implementation details for       
/// any platform view within the project. Basically it is used to          
/// create windows for linux, windows or mac os which we can render to
/// at specific point.
/// </summary>
//-----------------------------------------------------------------------------
class skyWindow : public skyIWindow
{

public:
	//-------------------------------------------------------------------------
    // Constructors & Destructors
    //-------------------------------------------------------------------------
	skyWindow::skyWindow();
	skyWindow::~skyWindow(void);

	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual skyResult skyWindow::VInitialize ( std::wstring title, int width, int height, bool isFullscreen, 
														int colorBits, int depthBits, int alphaBits );
	virtual skyResult skyWindow::VCreate ( void );
	virtual bool skyWindow::VPeekMessages ( void );

	virtual HWND skyWindow::VGetHwnd ( void ) 
	{
		return mHWnd;
	}
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	HINSTANCE mInstance; 
	HINSTANCE mPrevInstance;
	HWND mHWnd;
	MSG mMSG;
	LPWSTR mCmdLine; 
	std::wstring mClassName;
	WNDCLASSEX mWndClassEx;

	std::wstring mTitle;

	int mWidth;
	int mHeight;
	int mCmdShow;
	int mFormat;
	int mColorBits;
	int mDepthBits;
	int mAlphaBits;

	bool mIsFullscreen;
	bool mIsInitialized;
	bool mIsCreated;
	
	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
    // Static Private Methods
    //-------------------------------------------------------------------------
	static LRESULT CALLBACK skyWindow::WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


};
#endif