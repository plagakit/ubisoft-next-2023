#pragma once

#include <stdafx.h>

#include "Scene/Components/Transform/Transform.h"

class Scene;

class PhysicsSystem {

public:
	PhysicsSystem(Scene* scene);
	void UpdatePosition(Entity id, float deltaTime);

private:
	Scene* scene;

};