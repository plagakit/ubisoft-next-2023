#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

class TimerSystem : public ISystem {

public:
	void Update(Scene& scene);

};