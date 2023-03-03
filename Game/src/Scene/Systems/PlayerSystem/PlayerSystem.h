#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"

class Scene;

class PlayerSystem {

	const float ACCELERATION = 25.0f;
	const float WALK_SPEED = 100.0f;
	const float KICK_TIME = 0.25f;

public:

	Signal<> s_PlacedBomb;
	Signal<> s_Kicked;

	void CreatePlayer(Scene& scene, Entity id);
	void UpdatePlayers(Scene& scene);

	void OnDoneKick(Scene& scene, Entity id);

};