#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;

class PlayerSystem {

	const float ACCELERATION = 25.0f;
	const float WALK_SPEED = 100.0f;
	const float KICK_TIME = 0.5f;

public:

	Signal<Entity> s_PlacedBomb;
	Signal<Entity> s_Kicked;

	void CreatePlayer(Scene& scene, Entity id);
	void UpdatePlayers(Scene& scene);

	void OnDoneKick(Entity id);

};