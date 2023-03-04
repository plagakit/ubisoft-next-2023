#include <stdafx.h>

#include "BombSystem.h"

#include "Scene/Scene.h"
#include "Utils/Utils.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/Timer/Timer.h"
#include "Scene/Components/Bomb/Bomb.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/PrimitiveComponents.h"


void BombSystem::UpdateBombs(Scene& scene)
{
	for (Entity id : scene.GetEntities<Bomb>())
	{
		// Deaccelerate from kick/other movements
		Physics& ph = scene.GetComponent<Physics>(id);
		ph.velocity.x -= DEACCELERATION * Utils::Sign(ph.velocity.x);
		ph.velocity.y -= DEACCELERATION * Utils::Sign(ph.velocity.y);

		// Pulse scale faster and faster
		Transform& tf = scene.GetComponent<Transform>(id);
		const Timer& tm = scene.GetComponent<Timer>(id);
		float pulse = Utils::Lerp(1.0f, 1.25f, abs(sinf(tm.elapsed * tm.PercentElapsed() * 10.0f)));
		tf.scale = Vector2(pulse, pulse);
	}
}

void BombSystem::CreateBomb(Scene& scene, Entity player)
{
	Entity id = scene.CreateEntity();

	Transform tf = Transform();
	tf.position = scene.GetComponent<Transform>(player).position;
	scene.AddComponent<Transform>(id, tf);

	Timer tm = Timer(EXPLODE_TIME);
	tm.Start();
	scene.AddComponent<Timer>(id, tm);

	// Red wireframe circle w/ radius 30 and 16 segments
	Wireframe wf = Wireframe();
	wf.r = 255; wf.b = 0; wf.g = 0;
	std::vector<Vector2> points;
	for (float a = 0; a <= 2 * PI; a += 2 * PI / 16)
		points.push_back(Vector2(cosf(a) * 30, sinf(a) * 30));
	wf.points = points;
	scene.AddComponent<Wireframe>(id, wf);
	
	scene.AddComponent<Physics>(id, Physics(Physics::KINEMATIC, true));
	scene.AddComponent<CircleBounds>(id, CircleBounds(30));
	scene.AddComponent<Bomb>(id, Bomb(player, Bomb::Type::CROSS));
}

void BombSystem::ExplodeBomb(Scene& scene, Entity bomb)
{
	s_BombExploded.Emit(scene, bomb);
	for (int i = 0; i < 50; i++)
		CreateExplosionParticle(scene, bomb);
	scene.QueueDelete(bomb);
}

void BombSystem::CreateExplosionParticle(Scene& scene, Entity bomb)
{
	const Transform& btf = scene.GetComponent<Transform>(bomb);
	Entity id = scene.CreateEntity();

	Transform tf = Transform();
	tf.position = btf.position;
	scene.AddComponent<Transform>(id, tf);

	Physics ph = Physics(Physics::KINEMATIC);
	ph.velocity = Utils::RandUnitCircleVector() * Utils::RandFloat(BOMB_PARTICLE_SPEED.first, BOMB_PARTICLE_SPEED.second);
	ph.angularVelocity = Utils::RandFloat(BOMB_PARTICLE_ROTATION_SPEED.first, BOMB_PARTICLE_ROTATION_SPEED.second);
	scene.AddComponent<Physics>(id, ph);

	Wireframe wf = Wireframe();
	wf.r = 255; wf.b = 0; wf.g = 0;
	wf.points = { Vector2(0, -4.0f), Vector2(0, 4.0f) };
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Timer>(id, Timer(Utils::RandFloat(BOMB_PARTICLE_LIFETIME.first, BOMB_PARTICLE_LIFETIME.second), true, true));
	scene.AddComponent<Particle>(id, 0);
}


void BombSystem::OnTimerDone(Scene& scene, Entity id)
{
	if (scene.HasComponent<Bomb>(id))
		ExplodeBomb(scene, id);
}