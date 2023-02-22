#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"

struct BoxBounds {

	Vector2 offset;
	float width;
	float height;

	BoxBounds(float width, float height, Vector2 offset = Vector2());

};