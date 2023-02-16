#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISignalManager/ISignalManager.h"

class TimerSystem : public ISignalManager {

public:
	void UpdateTimers(Scene& scene);

};