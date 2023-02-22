#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"

struct CircleBounds {

	Vector2 offset;
	float radius;

	CircleBounds(float radius, Vector2 offset = Vector2());
};