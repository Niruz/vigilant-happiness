#pragma once

#define Clock SimpleTimer::Instance()


//this library must be included
#pragma comment(lib, "winmm.lib")

#include <windows.h>

class SimpleTimer
{
private:

	double mStartTime;

	SimpleTimer()
	{
		mStartTime = timeGetTime() * 0.001;
	}
	SimpleTimer(const SimpleTimer&);
	SimpleTimer& operator=(const SimpleTimer&);

public:

	static SimpleTimer* Instance();

	double GetCurrentTimeInSeconds() { return timeGetTime() * 0.001 - mStartTime; }
	double GetCurrentTimeInMillis() { return timeGetTime() - mStartTime; }
};