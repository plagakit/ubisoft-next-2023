#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"
#include "Core/Color/Color.h"

struct Wireframe {

	std::vector<Vector2> points;
	Color color;

	Wireframe();
	Wireframe(Color col);

};