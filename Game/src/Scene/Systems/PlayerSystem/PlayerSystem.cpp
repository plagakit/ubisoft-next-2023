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
#include "Scene/Components/Bomb/Bomb.h"


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
	scene.AddComponent<Timer>(id, Timer(KICK_TIME));
	scene.AddComponent<Player>(id, Player());
}

void PlayerSystem::UpdatePlayers(Scene& scene)
{
	for (Entity id : scene.GetEntities<Player>())
	{
		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);
		Player& pl = scene.GetComponent<Player>(id);
		
		// Input
		bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false);
		bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false);
		bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false);
		bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false);
		
		// For some reason, XINPUT_GAMEPAD_A/B can't be triggered on my keyboard, so I check for Z and X instead
		bool placeBomb = App::GetController().CheckButton(XINPUT_GAMEPAD_A, true) || App::IsKeyPressed('Z');
		bool kick = App::GetController().CheckButton(XINPUT_GAMEPAD_B, true) || App::IsKeyPressed('X');

		// MOVEMENT
		if (up)		ph.velocity.y += ACCELERATION;
		if (down)	ph.velocity.y -= ACCELERATION;
		if (right)	ph.velocity.x += ACCELERATION;
		if (left)	ph.velocity.x -= ACCELERATION;
		
		if (!up && !down && abs(ph.velocity.y) > 0.0f)
			ph.velocity.y -= ACCELERATION * Utils::Sign(ph.velocity.y);

		if (!left && !right && abs(ph.velocity.x) > 0.0f)
			ph.velocity.x -= ACCELERATION * Utils::Sign(ph.velocity.x);

		if (pl.kicking)
			ph.velocity = Vector2(0, 0);
		else
		{
			ph.velocity.x = Utils::Clamp(ph.velocity.x, -WALK_SPEED, WALK_SPEED);
			ph.velocity.y = Utils::Clamp(ph.velocity.y, -WALK_SPEED, WALK_SPEED);
		}

		// Rotate towards movement direction
		if (!ph.velocity.ApproxEqual(Vector2(0, 0)))
			tf.rotation = ph.velocity.Atan2() - PI/2;

		// Actions
		if (placeBomb && !pl.bombOut) 
		{ 
			pl.bombOut = true;
			s_PlacedBomb.Emit(scene, id); 
		}

		if (kick && !pl.kicking)
		{
			pl.kicking = true;
			s_Kicked.Emit(scene, id);
			scene.GetComponent<Timer>(id).Start();
		}
	}
}

void PlayerSystem::KickBomb(Scene& scene, Entity player, Entity bomb)
{
	const Transform& ptf = scene.GetComponent<Transform>(player);
	Physics& bph = scene.GetComponent<Physics>(bomb);

	Vector2 direction = Vector2(cosf(ptf.rotation + PI/2), sinf(ptf.rotation + PI/2));
	bph.velocity = direction * KICK_SPEED;
}


void PlayerSystem::OnTimerDone(Scene& scene, Entity id)
{
	if (scene.HasComponent<Player>(id))
	{
		Player& pl = scene.GetComponent<Player>(id);
		pl.kicking = false;
	}
}

void PlayerSystem::OnBombExplode(Scene& scene, Entity id)
{
	Entity creator = scene.GetComponent<Bomb>(id).creator;
	for (Entity player : scene.GetEntities<Player>())
		if (player == creator)
			scene.GetComponent<Player>(player).bombOut = false;
}

void PlayerSystem::OnTrigger(Scene& scene, Entity id1, Entity id2)
{
	if (scene.HasComponent<Player>(id1))
	{
		if (scene.GetComponent<Player>(id1).kicking && scene.HasComponent<Bomb>(id2))
			KickBomb(scene, id1, id2);
	}
}