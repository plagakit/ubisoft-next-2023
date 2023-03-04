#include <stdafx.h>

#include "ZombieSystem.h"

#include "Utils/Utils.h"
#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/DamageField/DamageField.h"
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/Zombie/Zombie.h"
#include "Scene/Components/Player/Player.h"

void ZombieSystem::UpdateZombies(Scene& scene)
{
	const auto& players = scene.GetEntities<Player>();

	if (players.size() == 0)
	{

	}
	else
	{
		for (Entity id : scene.GetEntities<Zombie>())
		{
			Transform& tf = scene.GetComponent<Transform>(id);
			Physics& ph = scene.GetComponent<Physics>(id);
			Zombie& zm = scene.GetComponent<Zombie>(id);
			
			float closestDist = 1e+020f; // pretty far!
			Vector2 closestPos;
			for (Entity player : players)
			{
				const Vector2& pos = scene.GetComponent<Transform>(player).position;
				float dist = tf.position.DistanceSquared(pos);
				if (closestDist > dist)
				{
					closestDist = dist;
					closestPos = pos;
				}
			}

			ph.velocity = (closestPos - tf.position).Normalized() * zm.walkSpeed;
			tf.rotation = ph.velocity.Atan2() + PI / 2;

		}
	}
}

Entity ZombieSystem::CreateZombie(Scene& scene, Vector2 pos)
{
	Entity zomb = scene.CreateEntity();

	Transform tf = Transform(pos);
	tf.scale *= 0.8f;
	scene.AddComponent<Transform>(zomb, tf);

	Wireframe wf = Wireframe(Color(Colors::GREEN));
	wf.points = {
		Vector2(30, 0), Vector2(16, -26), Vector2(-16, -26), Vector2(-30, 0), // bottom half
		Vector2(-30, 10), Vector2(-40, 10), Vector2(-36, -10), Vector2(-30, 10), // left arm
		Vector2(-30, 0), Vector2(-16, 26), Vector2(16, 26), Vector2(30, 0), // top half
		Vector2(30, 10), Vector2(40, 10), Vector2(36, -10), Vector2(30, 10), // right arm
	};
	scene.AddComponent<Wireframe>(zomb, wf);

	scene.AddComponent<Physics>(zomb, Physics(Physics::KINEMATIC));
	scene.AddComponent<CircleBounds>(zomb, CircleBounds(25));
	scene.AddComponent<Health>(zomb, DEFAULT_HEALTH);
	scene.AddComponent<Zombie>(zomb, Zombie());

	return zomb;
}

void ZombieSystem::CreateZombieGutsParticle(Scene& scene, Vector2 pos)
{
	Entity id = scene.CreateEntity();

	Transform tf = Transform(pos);
	tf.rotation = Utils::RandFloat(0.0f, 2 * PI);
	scene.AddComponent<Transform>(id, tf);

	Physics ph = Physics(Physics::KINEMATIC);
	Vector2 vel = Utils::RandUnitCircleVector() * Utils::RandFloat(GUTS_SPEED);
	ph.velocity = vel;
	ph.acceleration = vel * -0.75f;
	scene.AddComponent<Physics>(id, ph);

	Wireframe wf = Wireframe(Color(Colors::GREEN));
	wf.points = { Vector2(-2, -2), Vector2(0, 2), Vector2(2, -2) };
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Timer>(id, Timer(Utils::RandFloat(GUTS_LIFETIME), true, true));
	scene.AddComponent<Particle>(id, 0);
}


void ZombieSystem::OnDied(Scene& scene, Entity id)
{
	if (scene.HasComponent<Zombie>(id))
	{
		Vector2 pos = scene.GetComponent<Transform>(id).position;
		for (int i = 0; i < GUTS_COUNT; i++)
			CreateZombieGutsParticle(scene, pos);

		scene.QueueDelete(id);
	}
}