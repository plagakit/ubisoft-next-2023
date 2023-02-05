#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_entities(-1),
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
	/*m_transforms.RemoveComponent(id);
	m_sprites.RemoveComponent(id);*/
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = 0;

	CreateComponentArray<Transform>();
	CreateComponentArray<Sprite>();

	for (int i = 0; i < 5; i++)
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
}

void Scene::Update(float deltaTime)
{	
	m_deltaTime = deltaTime / 1000.0f; // deltaTime in seconds, want milliseconds
	
	for (int id = 1; id <= m_entities; id++)
		m_physicsSystem.UpdatePosition(id);	
}

void Scene::Render()
{
	for (int id = 1; id <= m_entities; id++)
		m_renderSystem.Render(id);
}
