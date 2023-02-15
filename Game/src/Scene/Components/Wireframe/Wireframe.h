#pragma once

#include <stdafx.h>

#include <Scene/Vector2/Vector2.h>

struct Wireframe {

	std::vector<Vector2> points;
	unsigned char r, g, b;

	Wireframe();

};