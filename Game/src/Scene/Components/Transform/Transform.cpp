#include <stdafx.h>

#include "Transform.h"

Transform::Transform() : 
	position(Vector2()), scale(Vector2(1.0f, 1.0f)), rotation(0.0f)
{}

Transform::Transform(Vector2 pos) :
	position(Vector2(pos.x, pos.y)), scale(Vector2(1.0f, 1.0f)), rotation(0.0f)
{}