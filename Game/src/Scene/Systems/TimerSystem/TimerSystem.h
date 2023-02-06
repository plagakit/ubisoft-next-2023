#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"


class TimerSystem : public ISystem {
	using ISystem::ISystem;

public:
	void Update(Entity id);

};