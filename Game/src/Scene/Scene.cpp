#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_renderSystem(RenderSystem(this)), 
	m_physicsSystem(PhysicsSystem(this)),
	m_timerSystem(TimerSystem(this))
{}

void Scene::Init()
{
	m_entityMgr.Init();

	m_entityMgr.CreateComponentArray<Transform>();
	m_entityMgr.CreateComponentArray<Sprite>();
	m_entityMgr.CreateComponentArray<Timer>();

	for (int i = 1; i <= 100; i++)
	{
		Entity ent = m_entityMgr.CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(250.0f, 250.0f);
		tf.velocity = Vector2(sin(std::rand()) * 50.0f, 150.0f);
		tf.scale = Vector2(0.25f, 0.25f);
		m_entityMgr.AddComponent<Transform>(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		m_entityMgr.AddComponent<Sprite>(ent, sp);

		Timer t = Timer(3);
		t.Start();
		m_entityMgr.AddComponent<Timer>(ent, t);
	}

	m_entityMgr.DeleteEntity(5);

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds


	Entity ent = m_entityMgr.CreateEntity();

	Transform tf = Transform();
	tf.position = Vector2(250.0f, 250.0f);
	tf.velocity = Vector2(sin(std::rand())*50.0f, 150.0f);
	tf.scale = Vector2(0.25f, 0.25f);
	m_entityMgr.AddComponent<Transform>(ent, tf);

	Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
	m_entityMgr.AddComponent<Sprite>(ent, sp);

	Timer t = Timer(3);
	t.Start();
	m_entityMgr.AddComponent<Timer>(ent, t);


	for (auto id : m_entityMgr.GetEntities<Timer>())
		m_timerSystem.Update(id);

	for (auto id : m_entityMgr.GetEntities<Transform>())
		m_physicsSystem.UpdatePosition(id);



}

void Scene::Render()
{
	for (auto id : m_entityMgr.GetEntities<Transform, Sprite>())
		m_renderSystem.Render(id);
}


EntityManager& Scene::GetEntityManager()
{
	return m_entityMgr;
}
