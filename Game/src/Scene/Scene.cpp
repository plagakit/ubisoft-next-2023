#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_entities(0),
	m_renderSystem(RenderSystem(this)), 
	m_physicsSystem(PhysicsSystem(this)),
	m_timerSystem(TimerSystem(this))
{}


int Scene::CreateEntity()
{
	m_entities++;
	return m_entities;
}

void Scene::DeleteEntity(Entity id)
{
	m_entities--;
	RemoveComponent<Transform>(id);
	RemoveComponent<Sprite>(id);
	RemoveComponent<Timer>(id);
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = 0;

	CreateComponentArray<Transform>();
	CreateComponentArray<Sprite>();
	CreateComponentArray<Timer>();

	for (int i = 1; i <= 5; i++)
	{
		int ent = CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(50.0f+50.0f*i, 250.0f);
		tf.velocity = Vector2(0.0f, 50.0f+(i*5.0f));
		tf.scale = Vector2(0.25f, 0.25f);
		AddComponent<Transform>(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		AddComponent<Sprite>(ent, sp);

		Timer t = Timer(2);
		AddComponent<Timer>(ent, t);
	}

	//DeleteEntity(1);
	GetComponent<Timer>(2).Start();

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds
	
	for (Entity id = 1; id <= m_entities; id++)
		m_timerSystem.Update(id);

	for (Entity id = 1; id <= m_entities; id++)
		m_physicsSystem.UpdatePosition(id);

	for (Entity id = 1; id <= m_entities; id++)
	{
		if (GetComponent<Timer>(id).done)
		{
			DeleteEntity(id);
			return;
		}
	}

}

void Scene::Render()
{
	std::string str = "";
	std::string timers = "";
	for (Entity id = 1; id <= m_entities; id++)
	{
		m_renderSystem.Render(id);
		str += std::to_string(id) + " ";
		timers += std::to_string(GetComponent<Timer>(id).PercentElapsed()) + " ";
	}

	App::Print(100, 600, std::to_string(m_entities).c_str());
	App::Print(100, 500, str.c_str());
	App::Print(100, 400, GetComponentArray<Sprite>()->ToString().c_str());
	App::Print(100, 300, timers.c_str());

}
