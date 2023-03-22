#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;

class TimerSystem {

public:

	Signal<> s_TimerDone;

	void UpdateTimers(Scene& scene);

};