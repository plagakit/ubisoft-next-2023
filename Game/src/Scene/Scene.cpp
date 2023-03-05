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
#include "Scene/Components/Zombie/Zombie.h"
#include "Scene/Components/PrimitiveComponents.h"


// Scene methods
Scene::Scene()
{
	m_count = 0;
	m_entities.clear();
	m_availableEntities.clear();

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push_back(i);

	// Initialize components
	m_typeCount = 0;
	m_componentArrays.clear();
	m_componentTypes.clear();
	m_removeComponentFunctions.clear();
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
	CreateComponentArray<Zombie>();
	CreateComponentArray<Wall>();
	CreateComponentArray<Particle>();

	// Bind systems
	m_timerSystem.s_TimerDone.Connect<ParticleSystem, &ParticleSystem::OnTimerDone>(&m_particleSystem);
	m_timerSystem.s_TimerDone.Connect<PlayerSystem, &PlayerSystem::OnTimerDone>(&m_playerSystem);
	m_timerSystem.s_TimerDone.Connect<BombSystem, &BombSystem::OnTimerDone>(&m_bombSystem);

	m_physicsSystem.s_onCollision.Connect<HealthSystem, &HealthSystem::OnCollision>(&m_healthSystem);

	m_physicsSystem.s_onTrigger.Connect<HealthSystem, &HealthSystem::OnTrigger>(&m_healthSystem);
	m_physicsSystem.s_onTrigger.Connect<PlayerSystem, &PlayerSystem::OnTrigger>(&m_playerSystem);
	m_physicsSystem.s_onTrigger.Connect<BombSystem, &BombSystem::OnTrigger>(&m_bombSystem);

	m_playerSystem.s_PlacedBomb.Connect<BombSystem, &BombSystem::CreateBomb>(&m_bombSystem);

	m_bombSystem.s_BombExploded.Connect<PlayerSystem, &PlayerSystem::OnBombExplode>(&m_playerSystem);
	m_bombSystem.s_BombExploded.Connect<Camera, &Camera::StartShake>(&m_camera);

	m_healthSystem.s_DamagedBy.Connect<PlayerSystem, &PlayerSystem::OnDamagedBy>(&m_playerSystem);

	m_healthSystem.s_Died.Connect<PlayerSystem, &PlayerSystem::OnDied>(&m_playerSystem);
	m_healthSystem.s_Died.Connect<ZombieSystem, &ZombieSystem::OnDied>(&m_zombieSystem);
}


void Scene::Init()
{
	// Initialize entities
	for (Entity id : m_entities)
		QueueDelete(id);
	DeleteQueuedEntities();

	m_count = 0;
	m_entities.clear();
	m_availableEntities.clear();
	m_deleteQueue.clear();

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push_back(i);

	// Initialize misc
	m_camera = Camera();

	// Since entities are unsigned, we can make 0 the "null entity". Any system that needs null entities can use 0!
	CreateEntity();

	// Create bomberman
	m_player = m_playerSystem.CreatePlayer(*this, Vector2(0, 0));
	m_ui.BindPlayer(*this, m_player);

	// Create map
	CreateWall(Vector2(-MAP_BOUNDS_X, 0), MAP_BOUND_WIDTH, MAP_LONG_HEIGHT);
	CreateWall(Vector2(MAP_BOUNDS_X, 0), MAP_BOUND_WIDTH, MAP_LONG_HEIGHT);
	CreateWall(Vector2(0, -MAP_BOUNDS_Y), MAP_LONG_WIDTH, MAP_BOUND_WIDTH);
	CreateWall(Vector2(0, MAP_BOUNDS_Y), MAP_LONG_WIDTH, MAP_BOUND_WIDTH);

	CreateWall(Vector2(-500, -250), 100, 300);
	CreateWall(Vector2(-500, 250), 100, 300);
	CreateWall(Vector2(500, -250), 100, 300);
	CreateWall(Vector2(500, 250), 100, 300);
	CreateWall(Vector2(0, -700), 100, 300);
	CreateWall(Vector2(0, 700), 100, 300);
	CreateWall(Vector2(0, -300), 300, 100);
	CreateWall(Vector2(0, 300), 300, 100);

	restartSceneTimer = Timer(RESTART_SCENE_TIME);

	for (int i = 0; i < 100; i++)
		m_zombieSystem.CreateZombie(*this, Vector2(i, 500));
}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime is in seconds, we want milliseconds
	
	auto const& players = GetEntities<Player>();
	auto const& zombies = GetEntities<Zombie>();
	auto const& walls = GetEntities<Wall>();
	auto const& bombs = GetEntities<Bomb>();

	// If player(s) are dead, restart scene
	if (players.size() <= 0)
	{
		if (restartSceneTimer.isRunning)
		{
			if (restartSceneTimer.elapsed > RESTART_SCENE_TIME) { Init(); }
			else { restartSceneTimer.elapsed += m_deltaTime; }
		}
		else { restartSceneTimer.Start(); }
	}
	else
	{
		// Camera follows player w/ slight drag
		m_camera.position = Utils::Lerp(m_camera.position, GetComponent<Transform>(players[0]).position, 0.05f);
		m_camera.Update(*this);
	}

	m_timerSystem.UpdateTimers(*this);
	m_playerSystem.UpdatePlayers(*this);
	m_zombieSystem.UpdateZombies(*this);
	m_bombSystem.UpdateBombs(*this);

	m_physicsSystem.UpdatePosition(*this);
	m_physicsSystem.UpdateCollision(*this, GetEntities<Physics, DamageField, Particle>(), GetEntities<Physics, Health>());
	m_physicsSystem.UpdateCollision(*this, players, walls);
	m_physicsSystem.UpdateCollision(*this, zombies, walls);
	m_physicsSystem.UpdateCollision(*this, bombs, walls);
	m_physicsSystem.UpdateCollision(*this, players, bombs);
	m_physicsSystem.UpdateCollision(*this, players, zombies);

	DeleteQueuedEntities();
}

void Scene::Render()
{
	m_renderSystem.Render(*this);
	m_ui.Render(*this);
}


// START OF ECS METHODS

// Entity methods

Entity Scene::GetCount()
{
	return m_count;
}

Signature& Scene::GetSignature(Entity id)
{
	return m_signatures.Get(id);
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

float Scene::AvailableEntitiesPercent()
{
	return 1 - float(m_count) / MAX_ENTITIES;
}


// Component methods

// ...which there are none of cuz they're all templated :P


// Misc methods

Camera& Scene::GetCamera()
{
	return m_camera;
}

// END OF ECS METHODS


Entity Scene::CreateWall(Vector2 pos, float width, float height)
{
	Entity wall = CreateEntity();

	Wireframe wf = Wireframe(Color(Colors::WHITE));
	wf.points = { Vector2(-width/2, -height/2), Vector2(width/2, -height/2), 
		Vector2(width/2, height/2), Vector2(-width/2, height/2)};
	AddComponent<Wireframe>(wall, wf);

	AddComponent<Transform>(wall, Transform(pos));
	AddComponent<BoxBounds>(wall, BoxBounds(width, height));
	AddComponent<Physics>(wall, Physics(Physics::STATIC));
	AddComponent<Wall>(wall, 0);

	return wall;
}