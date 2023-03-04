#pragma once

#include <stdafx.h>

struct Bomb {

	enum Type { CROSS, SINGLE };
	Type type;

	Entity creator;
	bool kicked;

	Bomb(Entity creator, Type type = Type::CROSS);

};