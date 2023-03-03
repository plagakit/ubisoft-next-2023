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

	// Create bomberman
	CreateBomberman(m_player);

	// Create box
	Entity wall = CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { Vector2(-50, -50), Vector2(50, -50), Vector2(50, 50), Vector2(-50, 50) };
	AddComponent<Wireframe>(wall, wf);

	Transform tf = Transform();
	tf.position = Vector2(-200, 200);
	AddComponent<Transform>(wall, tf);

	Physics ph = Physics(Physics::STATIC);
	AddComponent<Physics>(wall, ph);

	BoxBounds bb = BoxBounds(100,100);
	AddComponent<BoxBounds>(wall, bb);

	AddComponent<Timer>(wall, Timer(5));

	// Bind systems
	m_physicsSystem.s_onCollision.Connect<RenderSystem, &RenderSystem::Test>(&m_renderSystem);
}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime is in seconds, we want milliseconds
	
	// Camera follows player w/ slight drag
	m_camera.position = Utils::Lerp(m_camera.position, GetComponent<Transform>(m_player).position, 0.05f);

	m_timerSystem.UpdateTimers(*this);
	m_playerSystem.UpdatePlayers(*this);

	m_physicsSystem.UpdatePosition(*this);
	m_physicsSystem.UpdateCollision(*this, GetEntities<Physics>(), GetEntities<Physics>());

}

void Scene::Render()
{
	m_renderSystem.Render(*this);
}


void Scene::CreateBomberman(Entity& player)
{
	player = CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { 
		Vector2(-20, -20), // bottom left corner
		Vector2(20, -20), // bottom right corner
		Vector2(20, 0), // top right corner
		Vector2(0, 20), // head
		Vector2(-20, 0) // top left corner
	};
	AddComponent<Wireframe>(player, wf);

	AddComponent<Transform>(player, Transform());
	AddComponent<Physics>(player, Physics(Physics::KINEMATIC));
	AddComponent<CircleBounds>(player, CircleBounds(20));
	AddComponent<Player>(player, Player());
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

	s_EntityDeleted.Emit(id);
}

void Scene::QueueDelete(Entity id)
{
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