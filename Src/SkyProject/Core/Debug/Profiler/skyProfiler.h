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

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------
class skyProfilerSection; 
class skyGameApplication;

//-----------------------------------------------------------------------------
//  Name : skyProfiler (Class)
/// <summary>
/// Profiler class which will be instantiated in the game application class. 
/// </summary>
//-----------------------------------------------------------------------------
struct skyProfilerStat 
{
	int mCalls; 
	int mLastCalls;
	float mTime; 
	unsigned long mLastUpdate;
};

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Name : skyProfiler (Class)
/// <summary>
/// Profiler class which will be instantiated in the game application class. 
/// </summary>
//-----------------------------------------------------------------------------
class skyProfiler 
{
	friend class skyProfilerSection;
	friend class skyGameApplication;
public:
	//-------------------------------------------------------------------------
    // Constructor & Destructor
    //-------------------------------------------------------------------------
	skyProfiler::skyProfiler();
	skyProfiler::~skyProfiler();

	std::string skyProfiler::GetResult() 
	{
		return this->mDumpString; 
	}
private:
	//-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
	std::map<std::string, skyProfilerStat*> mSectionStats;
	std::string mDumpString; 
	unsigned long mLastTime;

	//-------------------------------------------------------------------------
    // Private Methods
    //-------------------------------------------------------------------------
	void skyProfiler::CountSection(std::string name, float time);
	void skyProfiler::GatherResults();
	int skyProfiler::FindLongestWord();


};