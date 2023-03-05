#pragma once

#include <stdafx.h>

struct Player {

	bool bombOut;
	enum ActionState { IDLE, KICKING, BEING_KNOCKED_BACK };
	ActionState actionState;

	Player();

};