#include <stdafx.h>

#include "Utils.h"

#include "Core/Vector2/Vector2.h"

int Utils::Sign(float f)
{
	return f < 0.0f ? -1 : f > 0.0f;
}

float Utils::Clamp(float f, float min, float max)
{
	// Smart compilers should hopefully compile this into assembly w/ no branches
	const float t = f < min ? min : f;
	return t > max ? max : t;
}

float Utils::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

Vector2 Utils::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return a + (b - a) * t;
}
