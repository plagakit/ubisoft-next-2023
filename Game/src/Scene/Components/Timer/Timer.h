#pragma once

#include <stdafx.h>

struct Timer {

	float duration;
	float elapsed;
	bool isRunning;
	bool done;
	bool oneFire;

	Timer();
	Timer(float duration, bool oneFire = true, bool startInstantly = false);

	void Start();
	float PercentElapsed() const;

};