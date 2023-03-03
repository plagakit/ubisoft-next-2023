#pragma once

#include <stdafx.h>


class Scene;

class PlayerSystem {

	const float ACCELERATION = 25.0f;
	const float WALK_SPEED = 50.0f;

public:
	void CreatePlayer(Scene& scene, Entity id);
	void UpdatePlayers(Scene& scene);

};