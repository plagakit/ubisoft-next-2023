#pragma once

#include <stdafx.h>

class Utils {

public:
	static inline int Sign(int i)
	{
		return i < 0 ? -1 : i > 0;
	}

	static inline int Sign(float f)
	{
		return f < 0 ? -1 : f > 0;
	}

	static inline float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	static inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return a + (b - a) * t;
	}
};