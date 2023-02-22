#pragma once

#include <stdafx.h>

#include "Scene/Systems/Signal/Signal.h"

class Scene;

class TimerSystem {

public:

	Signal<Entity> e_timerFired;

	void UpdateTimers(Scene& scene);

};