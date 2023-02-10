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

	m_componentMgr.CreateComponentArray<Transform>();
	m_componentMgr.CreateComponentArray<Sprite>();
	m_componentMgr.CreateComponentArray<Timer>();

	for (int i = 1; i <= 500; i++)
	{
		Entity ent = m_entityMgr.CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(50.0f+.5f*i, 250.0f);
		tf.velocity = Vector2(0.0f, 50.0f+(i*.1f));
		tf.scale = Vector2(0.25f, 0.25f);
		m_componentMgr.AddComponent<Transform>(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		m_componentMgr.AddComponent<Sprite>(ent, sp);

		Timer t = Timer(0.005f*(i+1));
		t.Start();
		m_componentMgr.AddComponent<Timer>(ent, t);
	}

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds
	
	for (auto id : m_entityMgr.GetEntities())
		m_timerSystem.Update(id);

	for (auto id : m_entityMgr.GetEntities())
		m_physicsSystem.UpdatePosition(id);

}

void Scene::Render()
{
	//std::string str = "";
	//std::string timers = "";
	for (auto id : m_entityMgr.GetEntities())
	{

		//str += std::to_string(id) + " ";
		//timers += std::to_string(m_componentMgr.GetComponent<Timer>(id).PercentElapsed()) + " ";
		m_renderSystem.Render(id);
	}

	//App::Print(100, 600, std::to_string(m_entityMgr.GetCount()).c_str());
	//App::Print(100, 500, str.c_str());
	//App::Print(100, 400, m_componentMgr.GetComponentArray<Sprite>()->ToString().c_str());
	//App::Print(100, 300, timers.c_str());
}


EntityManager& Scene::GetEntityManager()
{
	return m_entityMgr;
}

ComponentManager& Scene::GetComponentManager()
{
	return m_componentMgr;
}
