#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"


class PhysicsSystem : public ISystem {
	using ISystem::ISystem;

public:
	void UpdatePosition(Entity id);

};