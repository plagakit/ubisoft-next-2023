#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;

class TimerSystem {

public:

	Signal<Entity> s_timerDone;

	void UpdateTimers(Scene& scene);

};