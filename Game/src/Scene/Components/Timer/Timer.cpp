#include <stdafx.h>

#include "Timer.h"

Timer::Timer() :
	elapsed(0.0f), duration(0.0f), isRunning(false), oneFire(true), done(false)
{}

Timer::Timer(float dur, bool oneFr) :
	elapsed(0.0f), duration(dur), isRunning(false), oneFire(oneFr), done(false)
{}

void Timer::Start()
{
	elapsed = 0.0f;
	isRunning = true;
	done = false;
}

float Timer::PercentElapsed()
{
	return elapsed / duration;
}