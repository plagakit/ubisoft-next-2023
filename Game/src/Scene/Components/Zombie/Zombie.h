#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"

struct Zombie {

	float walkSpeed;
	Vector2 wallAvoidDir;

	float danceAnim;

	Zombie(float walkSpeed);

};