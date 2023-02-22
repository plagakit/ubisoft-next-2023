#pragma once

#include <stdafx.h>

struct Vector2 {

	float x, y;

	Vector2();
	Vector2(float newX, float newY);

	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator*(const Vector2& v) const;
	Vector2 operator/(float scalar) const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float scalar);
	Vector2& operator*=(const Vector2& v);
	Vector2& operator/=(float scalar);

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;
	bool ApproxEqual(const Vector2 & v, float epsilon) const;

	float Length() const;
	float LengthSquared() const;
	float Distance(const Vector2& to) const;
	Vector2 Normalized() const;
	Vector2 Rotated(float radians) const;
	float Atan2() const;

	std::string ToString() const;
};