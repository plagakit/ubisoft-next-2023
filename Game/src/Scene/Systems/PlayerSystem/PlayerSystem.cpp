#include <stdafx.h>

#include "PlayerSystem.h"

#include "Scene/Scene.h"
#include "Utils/Utils.h"
#include "Scene/Components/Player/Player.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"


void PlayerSystem::UpdatePlayers(Scene& scene)
{
	for (Entity id : scene.GetEntities<Player>())
	{

		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);
		
		if (App::IsKeyPressed('W'))
			ph.velocity.y += ACCELERATION;

		if (App::IsKeyPressed('S'))
			ph.velocity.y -= ACCELERATION;

		if (App::IsKeyPressed('D'))
			ph.velocity.x += ACCELERATION;

		if (App::IsKeyPressed('A'))
			ph.velocity.x -= ACCELERATION;

		
		// Slow down if key not pressed
		if (!App::IsKeyPressed('W') && !App::IsKeyPressed('S') && abs(ph.velocity.y) > 0.0f)
			ph.velocity.y -= ACCELERATION * Utils::Sign(ph.velocity.y);

		if (!App::IsKeyPressed('A') && !App::IsKeyPressed('D') && abs(ph.velocity.x) > 0.0f)
			ph.velocity.x -= ACCELERATION * Utils::Sign(ph.velocity.x);


		ph.velocity.x = Utils::Clamp(ph.velocity.x, -WALK_SPEED, WALK_SPEED);
		ph.velocity.y = Utils::Clamp(ph.velocity.y, -WALK_SPEED, WALK_SPEED);

		if (!ph.velocity.ApproxEqual(Vector2(0, 0)))
			tf.rotation = ph.velocity.Atan2() - PI/2;

	}
}