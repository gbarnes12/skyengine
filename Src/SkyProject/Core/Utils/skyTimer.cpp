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

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "skyTimer.h"

skyTimer::skyTimer()
{
	mFramesPerSecond = 0;
	mMaxFramesPerSecond = 0;
	mFrameCount = 0;

	mDelta = 0;
	mFixedDelta = 0.0f;
	mUseFixedStep = false;

	skyPlatform::PerformanceFrequency(&mTicksPerSecond64);
	skyPlatform::PerformanceCounter(&mCurrentTicks64);

	mStartupTicks64 = mCurrentTicks64;
	mOneSecTicks64 = mCurrentTicks64;
}

void skyTimer::Update()
{
	mLastTicks64 = mCurrentTicks64;
	skyPlatform::PerformanceCounter(&mCurrentTicks64);

	// Update the time increment
	
	if ( mUseFixedStep )
		mDelta = mFixedDelta;
	else
		mDelta = (float)((__int64)mCurrentTicks64 - (__int64)mLastTicks64) / (__int64)mTicksPerSecond64;

	// Continue counting the frame rate regardless of the time step.

	if ((float)((__int64)mCurrentTicks64 - (__int64)mOneSecTicks64)
		/ (__int64)mTicksPerSecond64 < 1.0f)
	{
		mFrameCount++;
	}
	else
	{
		mFramesPerSecond = mFrameCount;
		
		if ( mFramesPerSecond > mMaxFramesPerSecond )
			mMaxFramesPerSecond = mFramesPerSecond;

		mFrameCount = 0;
		mOneSecTicks64 = mCurrentTicks64;
	}
}

void skyTimer::Reset()
{
	mFramesPerSecond = 0;
	mFrameCount = 0;
	mDelta = 0;
}

float skyTimer::TotalTime()
{
	return ( (float)((__int64)mCurrentTicks64 - (__int64)mStartupTicks64)
		/(__int64)mTicksPerSecond64);
}

float skyTimer::ElapsedTime()
{
	return( mDelta );
}

int skyTimer::Framerate()
{
	return( mFramesPerSecond );
}

int skyTimer::MaxFramerate()
{
	return( mMaxFramesPerSecond );
}

int skyTimer::FrameCount()
{
	return( mFrameCount );
}


void skyTimer::SetFixedTimeStep( float step )
{
	if ( step <= 0.0f )
	{
		mUseFixedStep = false;
		mFixedDelta = 0.0f;
	}
	else
	{
		mUseFixedStep = true;
		mFixedDelta = step;
	}
}

