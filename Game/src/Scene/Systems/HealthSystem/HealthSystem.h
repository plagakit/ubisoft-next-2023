#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Vector2;

class HealthSystem {

public:

	Signal<Entity> s_DamagedBy;
	Signal<> s_Died;

	void ExecuteDamage(Scene& scene, Entity attacker, Entity target);

	void OnCollision(Scene& scene, Entity id1, Entity id2, Vector2 normal);
	void OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 normal);

};