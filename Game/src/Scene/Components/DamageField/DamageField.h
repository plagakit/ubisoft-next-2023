#pragma once

#include <stdafx.h>

struct DamageField {

	static const int MAX_HIT = 64;

	int damage;

	// alreadyHit keeps track of entities already hit to not spam them with damage.
	// Uses std::array b/c it has fixed memory size so it ensures contiguous DamageField vector for ECS.
	// Does not account for entities that are deleted but then new ones filling their id, however this is 
	// not a problem because damage fields should be active for only a short amount of time (pair them 
	// with a Particle & short Timer). 
	// Could pose a problem if hypothetically there was a type of enemy that spawns new enemies upon death, 
	// so that these new enemies instantly take the already-hit id of the old enemies and don't get hit as 
	// a result, but that's just a big hypothetical that is very much out of the scope of the project.
	int hitCount;
	std::array<Entity, MAX_HIT> alreadyHit;

	DamageField(int damage);
	bool TryHit(Entity id);
	bool AddHit(Entity id);

};