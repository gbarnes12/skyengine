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
// Name : skyProfiler.h                                                      //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// The profiler is used to analyze performance bottlenecks within the       //
/// engine. It will log all results into a table.                            //
/// </summary>                                                               //
//                                                                           //
/// <todo>                                                                   //
/// </todo>                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//---------------------------------------------------------------------------//

//-----------------------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------------------
#include "stdafx.h" 
#include "skyProfiler.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyProfiler (Class)
/// <summary>
/// Profiler class which will be instantiated in the game application class. 
/// </summary>
//-----------------------------------------------------------------------------
skyProfiler::skyProfiler()
{
	this->mLastTime =  skyPlatform::GetCPUTickCount();
}

skyProfiler::~skyProfiler()
{
	for(std::map<std::string, skyProfilerStat*>::iterator it = mSectionStats.begin(); it != this->mSectionStats.end(); it++)
	{
		SKY_SAFE_DELETE(it->second);
	}

	mSectionStats.clear();
}

void skyProfiler::CountSection(std::string name, float time)
{
	std::map<std::string, skyProfilerStat*>::iterator it = this->mSectionStats.find(name);
	if(it != this->mSectionStats.end()) 
	{
		it->second->mTime = time;

		// -1 = infinite till everything has been finished
		unsigned long currMs = skyPlatform::GetCPUTickCount();
		unsigned long maxMs = (it->second->mLastUpdate + 1000);

		if(currMs < maxMs) {
			it->second->mCalls++;
		}
		else {
			it->second->mLastCalls = it->second->mCalls;
			it->second->mCalls = 1;
			it->second->mLastUpdate = skyPlatform::GetCPUTickCount();
		}
	}
	else 
	{
		skyProfilerStat* stat = SKY_NEW skyProfilerStat;
		stat->mCalls = 1;
		stat->mLastCalls = 1;
		stat->mTime = time;
		stat->mLastUpdate = skyPlatform::GetCPUTickCount();

		this->mSectionStats.insert(std::make_pair(name, stat));
	}
}

int skyProfiler::FindLongestWord()
{
	int longestWord = 0;
	
	for(std::map<std::string, skyProfilerStat*>::iterator it = mSectionStats.begin(); it != this->mSectionStats.end(); ++it)
	{
		std::string name = it->first;
		int length = name.length();

		if(length >= longestWord)
			longestWord = length;
	}

	return longestWord;
}

void skyProfiler::GatherResults()
{
	unsigned long currMs = skyPlatform::GetCPUTickCount();
	unsigned long maxMs = (mLastTime + 200);

	if(currMs >= maxMs)
	{
		this->mDumpString = "Name\n";
		this->mDumpString += "---------\n";
		int longestWord = this->FindLongestWord();
		int wordPadding = 23;

		for(std::map<std::string, skyProfilerStat*>::iterator it = mSectionStats.begin(); it != this->mSectionStats.end(); ++it)
		{
			std::string name = it->first;
			int length = (longestWord + wordPadding) - name.length();

			if(name.length() == longestWord)
				length = wordPadding;

			std::string spaces = "";

			for(int i = 0; i < length; ++i)
				spaces += " ";

			float time = it->second->mTime * 1000;
			this->mDumpString += name + spaces + skyToString(it->second->mLastCalls) + "  " + skyToString(time) + "\n";
		}

		mLastTime = currMs;
	}
}
