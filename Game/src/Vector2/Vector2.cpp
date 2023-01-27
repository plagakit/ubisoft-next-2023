#include <stdafx.h>

#include "Vector2.h"

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float newX, float newY) : x(newX), y(newY) {}

Vector2 Vector2::operator+(const Vector2& v) const 
{
	return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(this->x / scalar, this->y / scalar);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

bool Vector2::ApproxEqual(const Vector2& v, float epsilon) const
{
	return abs(x - v.x) < epsilon && abs(y - v.y) < epsilon;
}

float Vector2::Length() const 
{
	return sqrtf(x * x + y * y);
}

float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

float Vector2::Distance(const Vector2& to) const
{
	return abs((to - *this).Length());
}

Vector2 Vector2::Normalize() const
{
	Vector2 v;
	if (LengthSquared() > 0)
		v = *this / Length();
	return v;
}

std::string Vector2::ToString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

