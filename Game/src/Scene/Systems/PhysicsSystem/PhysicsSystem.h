#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

class PhysicsSystem : public ISystem {

public:
	void Update(Scene& scene);

};