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
	RemoveComponent<Transform>(id);
	RemoveComponent<Sprite>(id);
	m_entities--;
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = -1;

	CreateComponentArray<Transform>();
	CreateComponentArray<Sprite>();

	for (int i = 0; i < 10; i++)
	{
		int ent = CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(20.0f*(i+1), 250.0f);
		tf.velocity = Vector2(0.0f, 50.0f);
		tf.scale = Vector2(0.25f, 0.25f);
		GetComponentArray<Transform>()->Add(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
		GetComponentArray<Sprite>()->Add(ent, sp);
	}

	DeleteEntity(0);

}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds
	
	for (Entity id = 0; id < m_entities; id++)
		m_physicsSystem.UpdatePosition(id);	
}

void Scene::Render()
{
	for (Entity id = 0; id < m_entities; id++)
		m_renderSystem.Render(id);
}
