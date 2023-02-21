#include <stdafx.h>

#include "Scene.h"
#include <Scene/EntityManager/EntityManagerTest.cpp>

#include <Scene/Components/Sprite/Sprite.h>
#include <Scene/Components/Transform/Transform.h>
#include <Scene/Components/Timer/Timer.h>
#include <Scene/Components/Wireframe/Wireframe.h>


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

	for (int i = 1; i <= 1000; i++)
	{
		Entity ent = m_entityMgr.CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(0.0f, 0.0f);
		tf.velocity = Vector2(sin(std::rand()) * 50.0f, 150.0f);
		tf.scale = Vector2(0.25f, 0.25f);
		m_entityMgr.AddComponent<Transform>(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		m_entityMgr.AddComponent<Sprite>(ent, sp);

		Timer t = Timer(2);
		t.Start();
		m_entityMgr.AddComponent<Timer>(ent, t);
	}


	Entity ent = m_entityMgr.CreateEntity();

	Wireframe wf = Wireframe();
	wf.points = { Vector2(-5, -5), Vector2(0, 10), Vector2(5, -5) };
	m_entityMgr.AddComponent<Wireframe>(ent, wf);

	Transform tf = Transform();
	tf.position = Vector2(0, 0);
	tf.scale = Vector2(5, 5);
	m_entityMgr.AddComponent<Transform>(ent, tf);

	//auto f = std::mem_fn(&RenderSystem::test);
	//auto b = std::bind(f, &m_renderSystem, std::placeholders::_1);
	//m_timerSystem.e_timerFired.Connect(RenderSystem::test);

	m_timerSystem.e_timerFired.Connect<RenderSystem, &RenderSystem::test>(&m_renderSystem);

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds

	m_timerSystem.UpdateTimers(*this);
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
