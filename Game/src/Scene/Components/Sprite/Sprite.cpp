#include <stdafx.h>

#include "Sprite.h"

Sprite::Sprite() : width(0.0f), height(0.0f), r(255), g(255), b(255) {}

Sprite::Sprite(float w, float h, int nr, int nb, int ng) :
	width(w), height(h), r(nr), b(nb), g(ng) {}

