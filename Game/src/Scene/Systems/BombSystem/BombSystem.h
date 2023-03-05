#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Vector2;
struct DamageField;

class BombSystem {

	static constexpr float EXPLODE_TIME = 3.0f;
	static constexpr float DEACCELERATION = 5.0f;

	static constexpr float EXPLOSION_SIZE = 40.0f;
	static constexpr float DEFAULT_EXPLOSION_DURATION = 0.5f;
	static const int DEFAULT_DAMAGE = 1;

	// Defining the particle emission info feels wrong - what if I want it to change
	// during the game, or be controlled by something else? If I had more time, I
	// would have create a ParticleEmitter component to hold all the data like this
	// and something like a CreateParticle() function in ParticleSystem.cpp that uses
	// said ParticleEmitter, but I didn't have enough time. Hardcoding values like this
	// works for this game and its small scope, but had I more time I would account for
	// expansion.
	static const int BOMB_PARTICLE_COUNT = 50;
	static constexpr std::pair<float, float> BOMB_PARTICLE_SPEED = { 50.0f, 150.0f };
	static constexpr std::pair<float, float> BOMB_PARTICLE_ROTATION_SPEED = { -4.0f, 4.0f };
	static constexpr std::pair<float, float> BOMB_PARTICLE_LIFETIME = { 1.0f, 2.0f };

public:

	Signal<> s_BombExploded;

	void UpdateBombs(Scene& scene);
	void CreateBomb(Scene& scene, Entity player);
	void ExplodeBomb(Scene& scene, Entity bomb);
	void CreateExplosionParticle(Scene& scene, Vector2 pos);
	void CreateExplosionHitbox(Scene& scene, float width, float height, Vector2 pos, const DamageField& damage);
	void BounceOffWall(Scene& scene, Entity bomb, Entity wall, Vector2 normal);

	void OnTimerDone(Scene& scene, Entity id);
	void OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 normal);

};
