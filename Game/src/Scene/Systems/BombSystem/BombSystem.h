#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Vector2;
struct DamageField;

class BombSystem {

	const float EXPLODE_TIME = 3.0f;
	const float DEACCELERATION = 5.0f;

	const float DEFAULT_EXPLOSION_DURATION = 0.5f;
	const int DEFAULT_DAMAGE = 1;
	const float DEFAULT_KNOCKBACK = 0.0f;

	const std::pair<float, float> BOMB_PARTICLE_SPEED = { 50.0f, 150.0f };
	const std::pair<float, float> BOMB_PARTICLE_ROTATION_SPEED = { -4.0f, 4.0f };
	const std::pair<float, float> BOMB_PARTICLE_LIFETIME = { 1.0f, 2.0f };

public:

	Signal<> s_BombExploded;

	void UpdateBombs(Scene& scene);
	void CreateBomb(Scene& scene, Entity player);
	void ExplodeBomb(Scene& scene, Entity bomb);
	void CreateExplosionParticle(Scene& scene, Entity bomb);
	void CreateExplosionHitbox(Scene& scene, int width, int height, Vector2 pos, const DamageField& damage);

	void OnTimerDone(Scene& scene, Entity id);

};
