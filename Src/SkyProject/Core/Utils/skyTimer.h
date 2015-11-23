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
// Name : skyTimer.h                                                         //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// 
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //

class skyTimer
{
public:
	skyTimer::skyTimer();

	void skyTimer::Update();
	void skyTimer::Reset();
	float skyTimer::TotalTime();
	float skyTimer::ElapsedTime();
	int skyTimer::Framerate();
	int skyTimer::MaxFramerate();
	int skyTimer::FrameCount();

	void skyTimer::SetFixedTimeStep( float step );
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	unsigned __int64 mTicksPerSecond64;
	unsigned __int64 mStartupTicks64;
	unsigned __int64 mCurrentTicks64;
	unsigned __int64 mOneSecTicks64;
	unsigned __int64 mLastTicks64;

	float mDelta;
	int mFramesPerSecond;
	int mMaxFramesPerSecond;
	int mFrameCount;

	float mFixedDelta;
	bool mUseFixedStep;
};