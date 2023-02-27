#include <stdafx.h>

#include "Scene.h"
#include "Scene/EntityManager/EntityManagerTest.cpp"

#include "Scene/Components/Sprite/Sprite.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Timer/Timer.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"


// Scene methods

void Scene::Init()
{
	EntityManagerTest::RunTests();
	
	// Initialize entities
	m_count = 0;
	m_entities.clear();
	m_availableEntities = {};

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



	// Create ship
	Entity ent = CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { Vector2(-5, -5), Vector2(0, 10), Vector2(5, -5) };
	AddComponent<Wireframe>(ent, wf);

	Transform tf = Transform();
	tf.position = Vector2(0, 0);
	tf.scale = Vector2(5, 5);
	AddComponent<Transform>(ent, tf);

	Physics ph = Physics(Physics::KINEMATIC);
	AddComponent<Physics>(ent, ph);

	CircleBounds cb = CircleBounds(10);
	AddComponent<CircleBounds>(ent, cb);
}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds

	m_timerSystem.UpdateTimers(*this);
	m_playerSystem.UpdatePlayer(*this);
	m_physicsSystem.UpdatePosition(*this);

}

void Scene::Render()
{
	m_renderSystem.Render(*this);
}


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
