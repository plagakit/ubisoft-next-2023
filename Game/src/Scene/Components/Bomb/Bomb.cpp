#include <stdafx.h>

#include "Bomb.h"

Bomb::Bomb(Entity _creator, Type _type) :
	creator(_creator), type(_type), kicked(false)
{}