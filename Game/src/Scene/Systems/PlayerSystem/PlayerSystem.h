#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Vector2;

class PlayerSystem {

	const int DEFAULT_HEALTH = 2; // dies instantly
	const float ACCELERATION = 25.0f;
	const float WALK_SPEED = 100.0f;
	const float KICK_TIME = 0.25f;
	const float KICK_SPEED = 400.0f;

public:

	Signal<> s_PlacedBomb;
	Signal<> s_Kicked;

	void UpdatePlayers(Scene& scene);
	Entity CreatePlayer(Scene& scene, Vector2 pos);
	void KickBomb(Scene& scene, Entity player, Entity bomb);

	void OnTimerDone(Scene& scene, Entity id);
	void OnBombExplode(Scene& scene, Entity id);
	void OnTrigger(Scene& scene, Entity id1, Entity id2);
	void OnDied(Scene& scene, Entity id);

};