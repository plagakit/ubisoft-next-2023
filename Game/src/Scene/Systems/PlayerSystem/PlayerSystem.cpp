#include <stdafx.h>

#include "PlayerSystem.h"

#include "Scene/Scene.h"
#include "Utils/Utils.h"

#include "Scene/Components/Player/Player.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Timer/Timer.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"


void PlayerSystem::CreatePlayer(Scene& scene, Entity id)
{
	Wireframe wf = Wireframe();
	wf.points = {
		Vector2(-20, -20), // bottom left corner
		Vector2(20, -20), // bottom right corner
		Vector2(20, 0), // top right corner
		Vector2(0, 20), // head
		Vector2(-20, 0) // top left corner
	};
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Transform>(id, Transform());
	scene.AddComponent<Physics>(id, Physics(Physics::KINEMATIC));
	scene.AddComponent<CircleBounds>(id, CircleBounds(20));
	scene.AddComponent<Player>(id, Player());
}

void PlayerSystem::UpdatePlayers(Scene& scene)
{
	for (Entity id : scene.GetEntities<Player>())
	{

		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);
		
		// MOVEMENT
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

		// Rotate towards movement direction
		if (!ph.velocity.ApproxEqual(Vector2(0, 0)))
			tf.rotation = ph.velocity.Atan2() - PI/2;

	}
}