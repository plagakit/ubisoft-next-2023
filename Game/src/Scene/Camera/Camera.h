#pragma once

#include <stdafx.h>

#include "Core/Vector2/Vector2.h"
#include "Scene/Components/Timer/Timer.h"
class Scene;

struct Camera {
	
	Vector2 position;
	Vector2 offset; // offset for screen shake/other effects
	float rotation;
	float zoom;

	Timer shakeTimer;
	bool shaking;

	Camera();

	void Update(Scene& scene);
	void StartShake(Scene& scene, Entity _id);
};