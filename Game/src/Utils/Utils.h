#pragma once

#include <stdafx.h>

struct Vector2;

class Utils {

public:
	static bool Equalf(float f1, float f2, float epsilon = 1e-06);

	static int Sign(float f);

	static float Clamp(float f, float min, float max);

	static float Lerp(float a, float b, float t);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

	static float RandFloat(float min, float max);
	static Vector2 RandUnitCircleVector();

};