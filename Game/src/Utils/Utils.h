#pragma once

#include <stdafx.h>

struct Vector2;
struct Color;

class Utils {

public:
	static bool Equalf(float f1, float f2, float epsilon = 1e-06);

	static int Sign(float f);

	static float Clamp(float f, float min, float max);

	static float Lerp(float a, float b, float t);
	static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);
	static Color Lerp(const Color c1, const Color c2, float t);

	static int RandInt(int min, int max);
	static int RandInt(std::pair<int, int> range);
	static float RandFloat(float min, float max);
	static float RandFloat(std::pair<float, float> range); // note: std::pair is small enough to copy instead of const ref
	static Vector2 RandUnitCircleVector();

};