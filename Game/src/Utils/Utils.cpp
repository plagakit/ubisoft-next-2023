#include <stdafx.h>

#include "Utils.h"

#include "Core/Vector2/Vector2.h"
#include "Core/Color/Color.h"

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

Vector2 Utils::Lerp(const Vector2 a, const Vector2 b, float t)
{
	return a + (b - a) * t;
}

Color Utils::Lerp(Color c1, Color c2, float t)
{
	return Color(
		static_cast<unsigned char>(Lerp(c1.r, c2.r, t)),
		static_cast<unsigned char>(Lerp(c1.g, c2.g, t)),
		static_cast<unsigned char>(Lerp(c1.b, c2.b, t))
	);
}

int Utils::RandInt(int min, int max)
{
	static std::mt19937 gen((unsigned int)std::time(nullptr));
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

int Utils::RandInt(std::pair<int, int> range)
{
	return RandInt(range.first, range.second);
}

float Utils::RandFloat(float min, float max)
{
	static std::mt19937 gen((unsigned int)std::time(nullptr));
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

float Utils::RandFloat(std::pair<float, float> range)
{
	return RandFloat(range.first, range.second);
}

Vector2 Utils::RandUnitCircleVector()
{
	static std::mt19937 gen((unsigned int)std::time(nullptr));
	std::uniform_real_distribution<float> dis(0, 2 * PI);
	float angle = dis(gen);
	return Vector2(cosf(angle), sinf(angle));
}