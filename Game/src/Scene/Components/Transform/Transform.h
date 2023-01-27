#pragma once

#include <stdafx.h>
#include <Scene/Vector2/Vector2.h>

struct Transform {

	Vector2 position, velocity, scale;
	float rotation;

	Transform();

};