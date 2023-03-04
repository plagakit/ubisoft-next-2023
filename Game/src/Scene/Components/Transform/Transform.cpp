#include <stdafx.h>

#include "Transform.h"

Transform::Transform() : 
	position(Vector2()), scale(Vector2(1.0f, 1.0f)), rotation(0.0f)
{}

Transform::Transform(Vector2 _position) :
	position(Vector2(_position.x, _position.y)), scale(Vector2(1.0f, 1.0f)), rotation(0.0f)
{}