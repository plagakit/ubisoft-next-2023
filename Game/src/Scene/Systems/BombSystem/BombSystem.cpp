#include <stdafx.h>

#include "BombSystem.h"

#include "Scene/Scene.h"
#include "Utils/Utils.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/Timer/Timer.h"
#include "Scene/Components/Bomb/Bomb.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/DamageField/DamageField.h"
#include "Scene/Components/PrimitiveComponents.h"


void BombSystem::UpdateBombs(Scene& scene)
{
	for (Entity id : scene.GetEntities<Bomb>())
	{
		// Deaccelerate from kick/other movements
		Physics ph = scene.GetComponent<Physics>(id);
		ph.velocity.x -= DEACCELERATION * Utils::Sign(ph.velocity.x);
		ph.velocity.y -= DEACCELERATION * Utils::Sign(ph.velocity.y);

		// Pulse scale faster and faster
		Transform tf = scene.GetComponent<Transform>(id);
		const Timer tm = scene.GetComponent<Timer>(id);
		float pulse = Utils::Lerp(1.0f, 1.25f, abs(sinf(tm.elapsed * tm.PercentElapsed() * 10.0f)));
		tf.scale = Vector2(pulse, pulse);

		scene.SetComponent<Physics>(id, ph);
		scene.SetComponent<Transform>(id, tf);
	}
}

// Components of a bomb: 
// Bomb, Transform, Timer, Wireframe, Physics, CircleBounds
void BombSystem::CreateBomb(Scene& scene, Entity player)
{
	Entity id = scene.CreateEntity();

	scene.AddComponent<Transform>(id, Transform(scene.GetComponent<Transform>(player).position));
	scene.AddComponent<Timer>(id, Timer(EXPLODE_TIME, true, true));

	// Red wireframe circle w/ radius 30 and 16 segments
	Wireframe wf = Wireframe(Color(Colors::RED));
	std::vector<Vector2> points;
	for (float a = 0; a <= 2 * PI; a += 2 * PI / 16)
		points.push_back(Vector2(cosf(a) * 25, sinf(a) * 25));
	wf.points = points;
	scene.AddComponent<Wireframe>(id, wf);
	
	scene.AddComponent<Physics>(id, Physics(Physics::KINEMATIC, true));
	scene.AddComponent<CircleBounds>(id, CircleBounds(30));
	scene.AddComponent<Bomb>(id, Bomb(player, Bomb::Type::CROSS));
}

void BombSystem::ExplodeBomb(Scene& scene, Entity bomb)
{
	const Bomb bombData = scene.GetComponent<Bomb>(bomb);
	const Transform tf = scene.GetComponent<Transform>(bomb);
	Vector2 bombPos = tf.position;

	switch (bombData.type)
	{

	case Bomb::CROSS:
		CreateExplosionHitbox(scene, EXPLOSION_SIZE, EXPLOSION_SIZE * 5, bombPos, DamageField(DEFAULT_DAMAGE));
		CreateExplosionHitbox(scene, EXPLOSION_SIZE * 5, EXPLOSION_SIZE, bombPos, DamageField(DEFAULT_DAMAGE));
		break;

	case Bomb::BIG:
		CreateExplosionHitbox(scene, EXPLOSION_SIZE * 4, EXPLOSION_SIZE * 4, bombPos, DamageField(DEFAULT_DAMAGE * 3));
		break;

	}
	
	for (int i = 0; i < BOMB_PARTICLE_COUNT; i++)
		CreateExplosionParticle(scene, bombPos);
	
	s_BombExploded.Emit(scene, bomb);
	scene.QueueDelete(bomb);
}

// Components of a bomb explosion particle: 
// Transform, Physics, Wireframe, Timer, Particle
void BombSystem::CreateExplosionParticle(Scene& scene, Vector2 pos)
{
	Entity id = scene.CreateEntity();

	scene.AddComponent<Transform>(id, Transform(pos));

	Physics ph = Physics(Physics::KINEMATIC);
	ph.velocity = Utils::RandUnitCircleVector() * Utils::RandFloat(BOMB_PARTICLE_SPEED);
	ph.angularVelocity = Utils::RandFloat(BOMB_PARTICLE_ROTATION_SPEED);
	scene.AddComponent<Physics>(id, ph);

	Wireframe wf = Wireframe(Color(Colors::RED));
	wf.points = { Vector2(0, -4.0f), Vector2(0, 4.0f) };
	scene.AddComponent<Wireframe>(id, wf);

	scene.AddComponent<Timer>(id, Timer(Utils::RandFloat(BOMB_PARTICLE_LIFETIME), true, true));
	scene.AddComponent<Particle>(id, 0);
}

// Components of a explosion hitbox: 
// Transform, Physics, Wireframe, BoxBounds, Timer, Particle, DamageField
void BombSystem::CreateExplosionHitbox(Scene& scene, float width, float height, Vector2 pos, const DamageField& damage)
{
	Entity hitbox = scene.CreateEntity();
	scene.AddComponent<Transform>(hitbox, Transform(pos));
	scene.AddComponent<Physics>(hitbox, Physics(Physics::STATIC, true));
	scene.AddComponent<BoxBounds>(hitbox, BoxBounds(width, height));
	scene.AddComponent<Timer>(hitbox, Timer(DEFAULT_EXPLOSION_DURATION, true, true));
	scene.AddComponent<Particle>(hitbox, 0);
	scene.AddComponent<DamageField>(hitbox, damage);

	float w = width / 2;
	float h = height / 2;
	Wireframe wf = Wireframe(Color(Colors::RED));
	wf.points = { Vector2(-w, -h), Vector2(w, -h), Vector2(w, h), Vector2(-w, h) };
	scene.AddComponent<Wireframe>(hitbox, wf);
}

void BombSystem::BounceOffWall(Scene& scene, Entity bomb, Entity wall, Vector2 normal)
{
	Physics ph = scene.GetComponent<Physics>(bomb);

	// Bounce horizontally
	if (abs(normal.x) > 0)
		ph.velocity.x *= -1;

	// Bounce vertically
	else if (abs(normal.y) > 0)
		ph.velocity.y *= -1;

	scene.SetComponent<Physics>(bomb, ph);
}


void BombSystem::OnTimerDone(Scene& scene, Entity id)
{
	if (scene.HasComponent<Bomb>(id))
		ExplodeBomb(scene, id);
}

void BombSystem::OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 normal)
{
	if (scene.HasComponent<Bomb>(id1) && scene.HasComponent<Wall>(id2))
		BounceOffWall(scene, id1, id2, normal);
}