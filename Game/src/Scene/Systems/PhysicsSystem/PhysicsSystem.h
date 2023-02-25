#pragma once

#include <stdafx.h>

class Scene;
struct Transform;
struct CircleBounds;
struct BoxBounds;

class PhysicsSystem {

public:
	void UpdatePosition(Scene& scene);

};