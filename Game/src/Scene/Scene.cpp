#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_entities(-1), // starts at 0
	m_renderSystem(RenderSystem(this)), m_physicsSystem(PhysicsSystem(this))
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
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = -1;

	CreateComponentArray<Transform>();
	CreateComponentArray<Sprite>();

	for (int i = 1; i <= 10; i++)
	{
		int ent = CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(50.0f+50.0f*i, 250.0f);
		tf.velocity = Vector2(0.0f, 50.0f+(i*5.0f));
		tf.scale = Vector2(0.25f, 0.25f);
		GetComponentArray<Transform>()->Add(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		GetComponentArray<Sprite>()->Add(ent, sp);
	}

	DeleteEntity(9);

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds
	
	for (Entity id = 0; id <= m_entities; id++)
		m_physicsSystem.UpdatePosition(id);	
}

void Scene::Render()
{
	std::string str = "";
	for (Entity id = 0; id <= m_entities; id++)
	{
		str += std::to_string(id) + " ";
		m_renderSystem.Render(id);
	}

	App::Print(100, 500, str.c_str());
	App::Print(100, 400, GetComponentArray<Sprite>()->ToString().c_str());
}
