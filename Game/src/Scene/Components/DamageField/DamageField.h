#pragma once

#include <stdafx.h>

struct DamageField {

	static const int MAX_HIT = 64;

	int damage;
	Signature hitSignature;

	// alreadyHit keeps track of entities already hit to not spam them with damage.
	// Uses std::array b/c it has fixed memory size so it ensures contiguous DamageField vector for ECS.
	// 
	// Does not account for entities that are deleted but then new ones filling their id, however this is 
	// not a problem because damage fields should be active for only a short amount of time (pair them 
	// with a Particle & short Timer).
	bool keepTrackOfAlreadyHit;
	int hitCount;
	std::array<Entity, MAX_HIT> alreadyHit;

	DamageField(int damage, bool keepTrackOfAlreadyHit = true);
	bool TryHit(Entity id, const Signature signature);
	bool AddHit(Entity id);
	void DontHitComponentID(ComponentID id);
	void HitComponentID(ComponentID id);

};