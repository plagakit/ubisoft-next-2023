#pragma once

#include <stdafx.h>

class Scene;
struct Vector2;

class ZombieSystem {

	const int DEFAULT_HEALTH = 1;

	const int GUTS_COUNT = 10;
	const std::pair<float, float> GUTS_SPEED = { 0.0f, 100.0f };
	const std::pair<float, float> GUTS_SCALE = { 0.8f, 1.2f };
	const std::pair<float, float> GUTS_LIFETIME = { 0.5f, 1.0f };


public:
	void UpdateZombies(Scene& scene);
	Entity CreateZombie(Scene& scene, Vector2 pos);
	void CreateZombieGutsParticle(Scene& scene, Vector2 pos);

	void OnDied(Scene& scene, Entity id);

};