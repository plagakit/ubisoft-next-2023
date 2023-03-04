#include <stdafx.h>

#include "Utils.h"

#include "Core/Vector2/Vector2.h"

bool Utils::Equalf(float f1, float f2, float epsilon)
{
	return abs(f1 - f2) < epsilon;
}

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

float Utils::RandFloat(float min, float max)
{
	static std::mt19937 gen(std::time(nullptr));
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

float Utils::RandFloat(const std::pair<float, float>& range)
{
	return RandFloat(range.first, range.second);
}

Vector2 Utils::RandUnitCircleVector()
{
	static std::mt19937 gen(std::time(nullptr));
	std::uniform_real_distribution<> dis(0, 2 * PI);
	float angle = dis(gen);
	return Vector2(cosf(angle), sinf(angle));
}