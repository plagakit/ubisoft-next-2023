#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Vector2;

class ZombieSystem {

public:

	static constexpr int DEFAULT_HEALTH = 1;
	static constexpr float DEFAULT_WALK_SPEED = 60.0f;

	static constexpr int GUTS_COUNT = 10;
	static constexpr std::pair<float, float> GUTS_SPEED = { 0.0f, 100.0f };
	static constexpr std::pair<float, float> GUTS_SCALE = { 0.8f, 1.2f };
	static constexpr std::pair<float, float> GUTS_LIFETIME = { 0.5f, 1.0f };

	Signal<> s_ZombieDied;

	void UpdateZombies(Scene& scene);
	Entity CreateZombie(Scene& scene, Vector2 pos, float walkSpeed = DEFAULT_WALK_SPEED);
	void CreateZombieGutsParticle(Scene& scene, Vector2 pos);

	void OnDied(Scene& scene, Entity id);

};