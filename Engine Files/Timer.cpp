//////////////////////////////////////////
//author: martin goulet
//TimeDr.cpp
//////////////////////////////////////////

#include "Timer.h"

//////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
//////////////////////////////////////////

Timer::Timer()
{
	//init class data
	this->Init();
}

Timer::~Timer()
{
	//release class data
	this->Release();
}

//////////////////////////////////////////
//METHODS
//////////////////////////////////////////

bool Timer::Init()
{
	//setup timer
	LARGE_INTEGER li;
	//init shit
	QueryPerformanceCounter(&li);
	this->lLastPolledInterval = 0.0f;
	//setup frequency
	LARGE_INTEGER li2;
	QueryPerformanceFrequency(&li2);
	this->fFreq = li2.LowPart;

	return true;
}

bool Timer::Release()
{
	//release shit
	return true;
}

float Timer::PollTimeInterval() const
{
	//returns time in seconds
	return this->lLastPolledInterval/this->fFreq;
}

float Timer::GetTime() const
{
	return timeGetTime();
}

bool Timer::UpdateTimeInterval()
{
	//get time from system clock
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	float ul = li.LowPart;
	//save last time in variable
	float lTempOld = this->lLastTime;
	//assign last time to the new current time
	this->lLastTime = ul;
	//return he difference in time
	this->lLastPolledInterval = ul-lTempOld;
	return true;
}
