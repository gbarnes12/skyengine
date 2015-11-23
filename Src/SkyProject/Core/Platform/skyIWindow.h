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
// Name : skyIWindow.h                                                       //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Basic interface that provides necessary implementation details for       //
/// any platform view within the project. Basically it is used to            //
/// create windows for linux, windows or mac os which we can render to       //
/// at specific point.                                                       //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

//-----------------------------------------------------------------------------
// Main Interface Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyIWindow (Interface)
/// <summary>
/// Basic interface that provides necessary implementation details for       
/// any platform view within the project. Basically it is used to          
/// create windows for linux, windows or mac os which we can render to
/// at specific point.
/// </summary>
//-----------------------------------------------------------------------------
class skyIWindow : public skyRefBaseClass
{
public:
	//-------------------------------------------------------------------------
    // Public Virtual Methods
    //-------------------------------------------------------------------------
	virtual skyResult skyIWindow::VInitialize ( std::wstring title, int width, int height, bool isFullscreen, 
													int colorBits, int depthBits, int alphaBits) = 0;
	virtual skyResult skyIWindow::VCreate ( void ) = 0;
	virtual bool skyIWindow::VPeekMessages ( void ) = 0;
	virtual HWND skyIWindow::VGetHwnd ( void ) = 0;
};