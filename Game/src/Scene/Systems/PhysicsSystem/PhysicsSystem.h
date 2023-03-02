#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;
struct Vector2;
struct Transform;
struct BoxBounds;
struct CircleBounds;

class PhysicsSystem {

public:
	Signal<Entity, Entity> s_onCollision;
	Signal<Entity, Entity> s_onTrigger;

	void UpdatePosition(Scene& scene);
	void UpdateCollision(Scene& scene, Entity one, Entity two);
	void UpdateCollision(Scene& scene, std::vector<Entity> group1, std::vector<Entity> group2);

private:
	bool IsColliding(Transform& tf1, Transform& tf2, CircleBounds& cb1, CircleBounds& cb2);
	bool IsColliding(Transform& tf1, Transform& tf2, BoxBounds& bb1, BoxBounds& bb2);
	bool IsColliding(Transform& tf1, Transform& tf2, CircleBounds& cb, BoxBounds& bb);

};