#include <stdafx.h>

#include "DamageField.h"

DamageField::DamageField(int _damage) :
	damage(_damage), hitCount(0), alreadyHit(std::array<Entity, MAX_HIT>())
{}

// Will check if the entity is already hit, if not add it to hit list and return true
// If already hit or max hits reached, returns false
bool DamageField::TryHit(Entity id)
{
	if (std::find(alreadyHit.begin(), alreadyHit.end(), id) == alreadyHit.end())
		return AddHit(id);
	else
		return false;
}

// Adds the entity to the hit list, returning false if the hit list is full
bool DamageField::AddHit(Entity id)
{
	if (hitCount > MAX_HIT)
		return false;

	alreadyHit[hitCount] = id;
	hitCount++;
	return true;
}