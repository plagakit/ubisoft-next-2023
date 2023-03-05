#include <stdafx.h>

#include "DamageField.h"

DamageField::DamageField(int _damage, bool keepTrack) :
	damage(_damage), keepTrackOfAlreadyHit(keepTrack),
	hitCount(0), alreadyHit(std::array<Entity, MAX_HIT>())
{
	// Set it to hit all types of components
	for (int i = 0; i < MAX_COMPONENT_TYPES; i++)
		hitSignature.set(i);
}

// Will check if signatures match, then if the entity is already hit, if not add it to hit list and return true
// If already hit or max hits reached, returns false
bool DamageField::TryHit(Entity id, Signature signature)
{
	if ((hitSignature & signature) == signature)
	{
		if (!keepTrackOfAlreadyHit)
			return true;
		else if (std::find(alreadyHit.begin(), alreadyHit.end(), id) == alreadyHit.end())
			return AddHit(id);
		else
			return false;
	}
	return false;
}

// Adds the entity to the hit list, returning false if the hit list is full
bool DamageField::AddHit(Entity id)
{
	if (hitCount >= MAX_HIT)
		return false;

	alreadyHit[hitCount] = id;
	hitCount++;
	return true;
}

void DamageField::DontHitComponentID(ComponentID id)
{
	hitSignature.set(id, false);
}

void DamageField::HitComponentID(ComponentID id)
{
	hitSignature.set(id);
}