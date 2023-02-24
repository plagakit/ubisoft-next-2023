#include <stdafx.h>

#include "Physics.h"

Physics::Physics(BodyType type, bool trigger) :
	bodyType(type), velocity(Vector2()), acceleration(Vector2()), angularVelocity(0.0f), isTrigger(trigger)
{}