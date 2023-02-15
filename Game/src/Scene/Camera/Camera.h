#pragma once

#include <stdafx.h>

#include "Scene/Vector2/Vector2.h"

struct Camera {

	Vector2 position;
	float rotation;
	float zoom;

	Camera();

};