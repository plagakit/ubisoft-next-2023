#pragma once

#include <stdafx.h>

struct DamageField {

	int damage;
	float knockback;

	DamageField(int damage, float knockback = 0.0f);

};