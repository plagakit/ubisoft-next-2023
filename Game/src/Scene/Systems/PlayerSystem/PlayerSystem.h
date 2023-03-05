#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
#include "Core/Color/Color.h"
class Scene;
struct Vector2;

class PlayerSystem {

	static const int DEFAULT_HEALTH = 3;
	Color PLAYER_COLOR = Color(Colors::LIGHT_BLUE);
	Color HURT_COLOR = Color(85, 158, 170);			// slight darker light blue with a twinge of red
	Color REALLY_HURT_COLOR = Color(128, 119, 128); // ouch!

	static constexpr float ACCELERATION = 25.0f;
	static constexpr float WALK_SPEED = 100.0f;
	static constexpr float ZOMBIE_KNOCKBACK = 1000.0f;
	static constexpr float KICK_TIME = 0.25f;
	static constexpr float KICK_SPEED = 400.0f;

	static const int DEATH_PARTICLE_COUNT = 20;
	static constexpr std::pair<float, float> DEATH_PARTICLE_SPEED = { 0.0f, 200.0f };
	static constexpr std::pair<float, float> DEATH_PARTICLE_LIFETIME = { 1.0f, 1.5f };

public:

	Signal<> s_PlacedBomb;
	Signal<> s_Kicked;

	void UpdatePlayers(Scene& scene);
	Entity CreatePlayer(Scene& scene, Vector2 pos);
	void KickBomb(Scene& scene, Entity player, Entity bomb);
	void GetHit(Scene& scene, Entity player, Entity zombie);
	void CreatePlayerDeathParticle(Scene& scene, Vector2 pos);

	void OnTimerDone(Scene& scene, Entity id);
	void OnBombExplode(Scene& scene, Entity id);
	void OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 normal);
	void OnDamagedBy(Scene& scene, Entity id1, Entity id2);
	void OnDied(Scene& scene, Entity id);

};