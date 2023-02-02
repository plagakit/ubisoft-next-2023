#pragma once

#include <stdafx.h>

#include <Scene/Vector2/Vector2.h>

struct Transform {

	Vector2 position;
	Vector2 velocity;
	Vector2 scale;
	float rotation;

	Transform();

};