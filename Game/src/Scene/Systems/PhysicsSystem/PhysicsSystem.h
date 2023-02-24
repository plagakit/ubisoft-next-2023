#pragma once

#include <stdafx.h>

class Scene;
struct Transform;
struct CircleBounds;
struct BoxBounds;

class PhysicsSystem {

public:
	void UpdatePosition(Scene& scene);

private:
	bool CheckCollision(Transform t1, Transform t2, CircleBounds c1, CircleBounds c2);
	bool CheckCollision(Transform t1, Transform t2, CircleBounds c, BoxBounds b);
	bool CheckCollision(Transform t1, Transform t2, BoxBounds b1, BoxBounds b2);

};