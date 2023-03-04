#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;

class BombSystem {

	const float EXPLODE_TIME = 3.0f;
	const float DEACCELERATION = 5.0f;

public:

	Signal<> s_BombExploded;

	void UpdateBombs(Scene& scene);
	void CreateBomb(Scene& scene, Entity player);
	void ExplodeBomb(Scene& scene, Entity bomb);
	void CreateBombParticle(Scene& scene);

	void OnTimerDone(Scene& scene, Entity id);

};
