//////////////////////////////////////////
//author: martin goulet
//Timer.h
//////////////////////////////////////////

/*
NOTE:
This class performs the time polling from the cmos clock.
*/

#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
#include <mmsystem.h>
#include <ctime>
#include "SubComponent.h"
//force include lib for timeGetTime()
#pragma comment( lib, "winmm.lib" )

const TIME_SCALE = 1000000;

class Timer: public SubComponent
{
private:
	//***VARIABLES***
	float lLastTime;
	float lLastPolledInterval;
	float fFreq;
	//init/release methods
	bool Init();
	bool Release();

public:
	//***CONSTRUCTORS//DESTRUCTOR
	Timer();
	~Timer();

	bool UpdateTimeInterval();
	float PollTimeInterval() const;
	float GetTime() const;

	//***ACCESSORS***

};

#endif TIMER_H