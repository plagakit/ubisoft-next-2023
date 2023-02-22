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


Scene::Scene() :
	m_entityMgr(10000)
{}

void Scene::Init()
{
	EntityManagerTest::RunTests();
	m_entityMgr.Init();
	
	m_entityMgr.CreateComponentArray<Transform>();
	m_entityMgr.CreateComponentArray<Sprite>();
	m_entityMgr.CreateComponentArray<Timer>();
	m_entityMgr.CreateComponentArray<Wireframe>();
	m_entityMgr.CreateComponentArray<Physics>();
	m_entityMgr.CreateComponentArray<BoxBounds>();
	m_entityMgr.CreateComponentArray<CircleBounds>();

	Entity ent = m_entityMgr.CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { Vector2(-5, -5), Vector2(0, 10), Vector2(5, -5) };
	m_entityMgr.AddComponent<Wireframe>(ent, wf);

	Transform tf = Transform();
	tf.position = Vector2(0, 0);
	tf.scale = Vector2(5, 5);
	m_entityMgr.AddComponent<Transform>(ent, tf);

	Physics ph = Physics(Physics::KINEMATIC);
	m_entityMgr.AddComponent<Physics>(ent, ph);

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


EntityManager& Scene::GetEntityManager()
{
	return m_entityMgr;
}

Camera& Scene::GetCamera()
{
	return m_camera;
}
