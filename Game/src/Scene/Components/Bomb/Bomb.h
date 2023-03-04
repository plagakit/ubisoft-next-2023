#pragma once

#include <stdafx.h>

struct Bomb {

	enum Type { CROSS, BIG, FAST };
	Type type;

	Entity creator;

	Bomb(Entity creator, Type type = Type::CROSS);

};