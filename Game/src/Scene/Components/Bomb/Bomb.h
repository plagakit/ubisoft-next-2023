#pragma once

#include <stdafx.h>

struct Bomb {

	enum Type { CROSS, SINGLE };
	Type type;

	int damage;


	Bomb(Type type = Type::CROSS, int damage = 1);

};