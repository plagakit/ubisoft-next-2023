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

Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(this->x * v.x, this->y * v.y);
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(this->x / scalar, this->y / scalar);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(this->x / v.x, this->y / v.y);
}

Vector2& Vector2::operator-()
{
	x = -x;
	y = -y;
	return *this;
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

Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
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

float Vector2::DistanceSquared(const Vector2& to) const
{
	return abs((to - *this).LengthSquared());
}

Vector2 Vector2::Normalized() const
{
	Vector2 v;
	float length = Length();
	if (length > 0)
		v = *this / length;
	return v;
}

Vector2 Vector2::Rotated(float r) const
{
	Vector2 v;
	v.x = x * cosf(r) - y * sinf(r);
	v.y = x * sinf(r) + y * cosf(r);
	return v;
}

float Vector2::Atan2() const
{
	return atan2f(y, x);
}

std::string Vector2::ToString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

