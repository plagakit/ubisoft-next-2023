#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;
struct BoxBounds;
struct CircleBounds;

class PhysicsSystem {

public:
	Signal<Entity, Entity> s_onCollision;
	Signal<Entity, Entity> s_onTrigger;
	void UpdatePosition(Scene& scene);

private:
	void UpdateCircleCollision(Scene& scene, Entity id, Entity other);
	void UpdateBoxCollision(Scene& scene, Entity id, Entity other);

	bool IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb1, CircleBounds& cb2);
	bool IsColliding(Scene& scene, Entity id1, Entity id2, BoxBounds& bb1, BoxBounds& bb2);
	bool IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb, BoxBounds& bb);

};