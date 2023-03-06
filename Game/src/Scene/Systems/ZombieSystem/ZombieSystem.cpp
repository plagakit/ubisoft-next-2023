#include <stdafx.h>

#include "ZombieSystem.h"

#include "Utils/Utils.h"
#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/DamageField/DamageField.h"
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/Zombie/Zombie.h"
#include "Scene/Components/Player/Player.h"

void ZombieSystem::UpdateZombies(Scene& scene)
{
	const auto& players = scene.GetEntities<Player>();

	if (players.size() == 0)
	{
		// Make the zombies do a lil dance when all players are dead
		for (Entity id : scene.GetEntities<Zombie>())
		{
			Transform tf = scene.GetComponent<Transform>(id);
			Physics ph = scene.GetComponent<Physics>(id);
			Zombie zm = scene.GetComponent<Zombie>(id);

			zm.danceAnim += scene.m_smoothDeltaTime;
			tf.rotation += scene.m_smoothDeltaTime * 2.0f;
			ph.velocity = Vector2(sinf(zm.danceAnim * 5.0f) * 30.0f, -cosf(zm.danceAnim * 5.0f) * 30.0f);

			scene.SetComponent<Transform>(id, tf);
			scene.SetComponent<Physics>(id, ph);
			scene.SetComponent<Zombie>(id, zm);
		}
	}
	else
	{
		for (Entity id : scene.GetEntities<Zombie>())
		{
			Transform tf = scene.GetComponent<Transform>(id);
			Physics ph = scene.GetComponent<Physics>(id);
			Zombie zm = scene.GetComponent<Zombie>(id);
			
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

			// Walk around walls to not get stuck
			// Simple sol'n to avoid walls without complex pathfinding
			// I *could've* implemented pathfinding with a grid of sorts -> spatial partioning! :D

			// TODO: make little ascii diagram, will trip up around corners

			// Hugging left/right wall
			if (abs(ph.collisionNormal.x) == 1)
			{
				// If not already avoiding a wall
				if (zm.wallAvoidDir == Vector2(0, 0))
				{
					// Avoid wall by walking adjacent to it in the direction of player	
					zm.wallAvoidDir = Vector2(-ph.collisionNormal.x, (float)Utils::Sign(closestPos.y - tf.position.y));
					ph.velocity = zm.wallAvoidDir * zm.walkSpeed;
				}
				// If the collision normal is pointing towards player, we can just unstick
				else if (Utils::Sign(ph.collisionNormal.x) == Utils::Sign(closestPos.x - tf.position.x))
				{
					zm.wallAvoidDir = Vector2(0, 0);
					ph.velocity = (closestPos - tf.position).Normalized() * zm.walkSpeed;
				}
			}
			// Hugging top/bottom wall
			else if (abs(ph.collisionNormal.y) == 1)
			{
				if (zm.wallAvoidDir == Vector2(0, 0))
				{
					zm.wallAvoidDir = Vector2((float)Utils::Sign(closestPos.x - tf.position.x), -ph.collisionNormal.y);
					ph.velocity = zm.wallAvoidDir * zm.walkSpeed;
				}
				else if (Utils::Sign(ph.collisionNormal.y) == Utils::Sign(closestPos.y - tf.position.y))
				{
					zm.wallAvoidDir = Vector2(0, 0);
					ph.velocity = (closestPos - tf.position).Normalized() * zm.walkSpeed;
				}
			}
			// If not stuck on a wall, just home in
			else
			{
				zm.wallAvoidDir = Vector2(0, 0);
				ph.velocity = (closestPos - tf.position).Normalized() * zm.walkSpeed;
			}
			
			tf.rotation = ph.velocity.Atan2() + PI / 2;

			scene.SetComponent<Transform>(id, tf);
			scene.SetComponent<Physics>(id, ph);
			scene.SetComponent<Zombie>(id, zm);
		}
	}
}

Entity ZombieSystem::CreateZombie(Scene& scene, Vector2 pos, float walkSpeed)
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
	
	DamageField df = DamageField(1, false);
	df.DontHitComponentID(scene.GetComponentType<Zombie>());
	scene.AddComponent<DamageField>(zomb, df);

	scene.AddComponent<Physics>(zomb, Physics(Physics::KINEMATIC));
	scene.AddComponent<BoxBounds>(zomb, BoxBounds(30, 30));
	scene.AddComponent<Health>(zomb, DEFAULT_HEALTH);
	scene.AddComponent<Zombie>(zomb, Zombie(walkSpeed));

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
		// Becomes too laggy too quickly :(
		//Vector2 pos = scene.GetComponent<Transform>(id).position;
		//for (int i = 0; i < GUTS_COUNT * scene.AvailableEntitiesPercent(); i++)
		//	CreateZombieGutsParticle(scene, pos);
		s_ZombieDied.Emit(scene, id);
		scene.QueueDelete(id);
	}
}