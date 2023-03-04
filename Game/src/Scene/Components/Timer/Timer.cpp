#include <stdafx.h>

#include "Timer.h"

Timer::Timer() :
	elapsed(0.0f), duration(0.0f), isRunning(false), oneFire(true), done(false)
{}

Timer::Timer(float _duration, bool _oneFire) :
	elapsed(0.0f), duration(_duration), isRunning(false), oneFire(_oneFire), done(false)
{}

void Timer::Start()
{
	elapsed = 0.0f;
	isRunning = true;
	done = false;
}

// Returns the percentage time elapsed from 0.0-1.0, can be inlined b/c very simple function
float Timer::PercentElapsed() const
{
	return elapsed / duration;
}