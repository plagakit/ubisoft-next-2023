#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"

struct Physics {

	enum BodyType { STATIC, KINEMATIC };
	BodyType bodyType;
	bool isTrigger;

	Vector2 velocity;
	Vector2 acceleration;
	float angularVelocity;

	Vector2 collisionNormal;

	Physics(BodyType bodyType, bool isTrigger = false);

};