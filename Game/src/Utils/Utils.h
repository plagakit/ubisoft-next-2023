#pragma once

#include <stdafx.h>

struct Vector2;

class Utils {

public:
	static int Sign(float f);

	static float Clamp(float f, float min, float max);

	static float Lerp(float a, float b, float t);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
};