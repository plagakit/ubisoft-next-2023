#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISignalManager.h"

class TimerSystem : public ISignalManager {

public:
	void UpdateTimers(Scene& scene);

};