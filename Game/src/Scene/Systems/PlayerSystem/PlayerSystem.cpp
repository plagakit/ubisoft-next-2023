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
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/Zombie/Zombie.h"


void PlayerSystem::UpdatePlayers(Scene& scene)
{
	for (Entity id : scene.GetEntities<Player>())
	{
		Transform tf = scene.GetComponent<Transform>(id);
		Physics ph = scene.GetComponent<Physics>(id);
		Player pl = scene.GetComponent<Player>(id);
		Timer kickTimer = scene.GetComponent<Timer>(id);

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

		switch (pl.actionState)
		{
		case Player::IDLE:
			ph.velocity.x = Utils::Clamp(ph.velocity.x, -WALK_SPEED, WALK_SPEED);
			ph.velocity.y = Utils::Clamp(ph.velocity.y, -WALK_SPEED, WALK_SPEED);
			break;

		case Player::KICKING:
			ph.velocity = Vector2(0, 0);
			break;
		}

		// Rotate towards movement direction
		if (!ph.velocity.ApproxEqual(Vector2(0, 0)))
			tf.rotation = ph.velocity.Atan2() - PI / 2;

		// Actions
		if (placeBomb && !pl.bombOut) 
		{ 
			pl.bombOut = true;
			s_PlacedBomb.Emit(scene, id); 
		}

		if (kick && pl.actionState == Player::IDLE)
		{
			pl.actionState = Player::KICKING;
			s_Kicked.Emit(scene, id);
			kickTimer.Start();
		}

		scene.SetComponent<Transform>(id, tf);
		scene.SetComponent<Physics>(id, ph);
		scene.SetComponent<Player>(id, pl);
		scene.SetComponent<Timer>(id, kickTimer);
	}
}

Entity PlayerSystem::CreatePlayer(Scene& scene, Vector2 pos)
{
	Entity id = scene.CreateEntity();

	Wireframe wf = Wireframe(Color(Colors::LIGHT_BLUE));
	wf.points = {
		Vector2(-20, -20), // bottom left corner
		Vector2(20, -20), // bottom right corner
		Vector2(20, 0), // top right corner
		Vector2(0, 20), // head
		Vector2(-20, 0) // top left corner
	};
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Transform>(id, Transform(pos));
	scene.AddComponent<Physics>(id, Physics(Physics::KINEMATIC));
	scene.AddComponent<CircleBounds>(id, CircleBounds(20));
	scene.AddComponent<Timer>(id, Timer(KICK_TIME));
	scene.AddComponent<Player>(id, Player());
	scene.AddComponent<Health>(id, DEFAULT_HEALTH);

	return id;
}

void PlayerSystem::KickBomb(Scene& scene, Entity player, Entity bomb)
{
	const Transform ptf = scene.GetComponent<Transform>(player);
	Physics bph = scene.GetComponent<Physics>(bomb);

	Vector2 direction = Vector2(cosf(ptf.rotation + PI/2), sinf(ptf.rotation + PI/2));
	bph.velocity = direction * KICK_SPEED;

	scene.SetComponent<Physics>(bomb, bph);
}

void PlayerSystem::GetHit(Scene& scene, Entity player, Entity zombie)
{
	const Transform ptf = scene.GetComponent<Transform>(player);
	const Transform ztf = scene.GetComponent<Transform>(zombie);
	Physics ph = scene.GetComponent<Physics>(player);
	Timer tm = scene.GetComponent<Timer>(player);
	Player pl = scene.GetComponent<Player>(player);

	Vector2 dir = (ptf.position - ztf.position).Normalized();
	ph.velocity = dir * ZOMBIE_KNOCKBACK;
	tm.Start();
	pl.actionState = Player::BEING_KNOCKED_BACK;

	scene.SetComponent<Physics>(player, ph);
	scene.SetComponent<Timer>(player, tm);
	scene.SetComponent<Player>(player, pl);
}

void PlayerSystem::CreatePlayerDeathParticle(Scene& scene, Vector2 pos)
{
	Entity id = scene.CreateEntity();

	scene.AddComponent<Transform>(id, Transform(pos));

	Physics ph = Physics(Physics::KINEMATIC);
	ph.velocity = Utils::RandUnitCircleVector() * Utils::RandFloat(DEATH_PARTICLE_SPEED);
	scene.AddComponent<Physics>(id, ph);

	Wireframe wf = Wireframe(Color(Colors::LIGHT_BLUE));
	wf.points = { Vector2(-2, -2), Vector2(0, 2), Vector2(2, -2) };
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Timer>(id, Timer(Utils::RandFloat(DEATH_PARTICLE_LIFETIME), true, true));
	scene.AddComponent<Particle>(id, 0);
}


void PlayerSystem::OnTimerDone(Scene& scene, Entity id)
{
	if (scene.HasComponent<Player>(id))
	{
		Player pl = scene.GetComponent<Player>(id);
		pl.actionState = Player::IDLE;
		scene.SetComponent<Player>(id, pl);
	}
}

void PlayerSystem::OnBombExplode(Scene& scene, Entity id)
{
	Entity creator = scene.GetComponent<Bomb>(id).creator;
	for (Entity player : scene.GetEntities<Player>())
	{
		if (player == creator)
		{
			Player pl = scene.GetComponent<Player>(player);
			pl.bombOut = false;
			scene.SetComponent<Player>(id, pl);
		}
	}
		
}

void PlayerSystem::OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 normal)
{
	if (scene.HasComponent<Player>(id1) && 
		scene.GetComponent<Player>(id1).actionState == Player::KICKING
		&& scene.HasComponent<Bomb>(id2))
	{
		KickBomb(scene, id1, id2);
	}
}

void PlayerSystem::OnDamagedBy(Scene& scene, Entity id1, Entity id2)
{
	if (scene.HasComponent<Player>(id1) && scene.HasComponent<Zombie>(id2))
		GetHit(scene, id1, id2);
}

void PlayerSystem::OnDied(Scene& scene, Entity id)
{
	if (scene.HasComponent<Player>(id))
	{
		Vector2 pos = scene.GetComponent<Transform>(id).position;
		for (int i = 0; i < DEATH_PARTICLE_COUNT; i++)
			CreatePlayerDeathParticle(scene, pos);

		scene.QueueDelete(id);
	}
}