#include <stdafx.h>

#include "Scene.h"

#include "Utils/Utils.h"

#include "Scene/Components/Sprite/Sprite.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Timer/Timer.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/Player/Player.h"
#include "Scene/Components/Bomb/Bomb.h"
#include "Scene/Components/DamageField/DamageField.h"
#include "Scene/Components/PrimitiveComponents.h"


// Scene methods
Scene::Scene()
{
	m_count = 0;
	m_entities.clear();
	m_availableEntities.clear();

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push_back(i);
}


void Scene::Init()
{
	// Initialize entities
	m_count = 0;
	m_entities.clear();
	m_availableEntities.clear();

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push_back(i);
	
	// Initialize components
	CreateComponentArray<Transform>();
	CreateComponentArray<Sprite>();
	CreateComponentArray<Timer>();
	CreateComponentArray<Wireframe>();
	CreateComponentArray<Physics>();
	CreateComponentArray<BoxBounds>();
	CreateComponentArray<CircleBounds>();
	CreateComponentArray<Player>();
	CreateComponentArray<Bomb>();
	CreateComponentArray<DamageField>();
	CreateComponentArray<Wall>();
	CreateComponentArray<Particle>();

	// Create bomberman
	m_player = CreateEntity();
	m_playerSystem.CreatePlayer(*this, m_player);

	// Create box
	Entity wall = CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { Vector2(-50, -50), Vector2(50, -50), Vector2(50, 50), Vector2(-50, 50) };
	AddComponent<Wireframe>(wall, wf);

	Transform tf = Transform();
	tf.position = Vector2(-200, 200);
	AddComponent<Transform>(wall, tf);

	BoxBounds bb = BoxBounds(100,100);
	AddComponent<BoxBounds>(wall, bb);

	AddComponent<Physics>(wall, Physics(Physics::STATIC));
	AddComponent<Timer>(wall, Timer(5));
	AddComponent<Wall>(wall, 0);


	// Bind systems
	m_timerSystem.s_TimerDone.Connect<ParticleSystem, &ParticleSystem::OnTimerDone>(&m_particleSystem);
	m_timerSystem.s_TimerDone.Connect<PlayerSystem, &PlayerSystem::OnTimerDone>(&m_playerSystem);
	m_timerSystem.s_TimerDone.Connect<BombSystem, &BombSystem::OnTimerDone>(&m_bombSystem);

	m_physicsSystem.s_onCollision.Connect<HealthSystem, &HealthSystem::OnCollision>(&m_healthSystem);

	m_physicsSystem.s_onTrigger.Connect<HealthSystem, &HealthSystem::OnTrigger>(&m_healthSystem);
	m_physicsSystem.s_onTrigger.Connect<PlayerSystem, &PlayerSystem::OnTrigger>(&m_playerSystem);

	m_playerSystem.s_PlacedBomb.Connect<BombSystem, &BombSystem::CreateBomb>(&m_bombSystem);

	m_bombSystem.s_BombExploded.Connect<PlayerSystem, &PlayerSystem::OnBombExplode>(&m_playerSystem);
	m_bombSystem.s_BombExploded.Connect<Camera, &Camera::StartShake>(&m_camera);

	//m_playerSystem.s_Kicked.Connect<RenderSystem, &RenderSystem::Test>(&m_renderSystem);
	//m_playerSystem.s_PlacedBomb.Connect<RenderSystem, &RenderSystem::Test>(&m_renderSystem);
}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime is in seconds, we want milliseconds
	
	// Camera follows player w/ slight drag
	m_camera.Update(*this);
	m_camera.position = Utils::Lerp(m_camera.position, GetComponent<Transform>(m_player).position, 0.05f);

	m_timerSystem.UpdateTimers(*this);
	m_playerSystem.UpdatePlayers(*this);
	m_bombSystem.UpdateBombs(*this);

	m_physicsSystem.UpdatePosition(*this);
	m_physicsSystem.UpdateCollision(*this, GetEntities<Player>(), GetEntities<Bomb>());
	m_physicsSystem.UpdateCollision(*this, GetEntities<Player>(), GetEntities<Wall>());
	m_physicsSystem.UpdateCollision(*this, GetEntities<Physics, DamageField>(), GetEntities<Physics, Health>());

	DeleteQueuedEntities();
}

void Scene::Render()
{
	m_renderSystem.Render(*this);
}


// START OF ECS METHODS

// Entity methods

Entity Scene::GetCount()
{
	return m_count;
}

bool Scene::DoesEntityExist(Entity id)
{
	return std::find(m_entities.begin(), m_entities.end(), id) != m_entities.end();
}

Entity Scene::CreateEntity()
{
	assert("Entity limit reached." && m_availableEntities.size() > 0);

	Entity id = m_availableEntities.front();
	m_availableEntities.pop_front();
	m_entities.push_back(id);
	m_signatures.Add(id, Signature());
	m_count++;

	return id;
}

void Scene::DeleteEntity(Entity id)
{
	auto entityIdx = std::find(m_entities.begin(), m_entities.end(), id);
	assert("Entity not found in vector!" && entityIdx != m_entities.end());

	m_count--;
	m_entities.erase(entityIdx);
	m_availableEntities.push_back(id);

	// For each component type in the signature, call its remove function!
	Signature& signature = m_signatures.Get(id);
	for (auto i = 0; i < signature.size(); i++)
		if (signature.test(i))
			m_removeComponentFunctions[i](id);

	s_EntityDeleted.Emit(*this, id);
}

void Scene::QueueDelete(Entity id)
{
	// Does nothing if the entity is already in the queue
	if (std::find(m_deleteQueue.begin(), m_deleteQueue.end(), id) == m_deleteQueue.end())
		m_deleteQueue.push_back(id);
}

void Scene::DeleteQueuedEntities()
{
	while (!m_deleteQueue.empty())
	{
		Entity id = m_deleteQueue.front();
		DeleteEntity(id);
		m_deleteQueue.pop_front();
	}
}

// Component methods

// ...which there are none of cuz they're all templated :P


// Misc methods

Camera& Scene::GetCamera()
{
	return m_camera;
}

// END OF NON-GAMEPLAY METHODS