#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_entities(0), m_sprites(), m_transforms(), m_renderSystem(this), m_physicsSystem(this)
{}

Transform& Scene::GetTransform(Entity id)
{
	return m_transforms.GetComponent(id);
}

Sprite& Scene::GetSprite(Entity id)
{
	return m_sprites.GetComponent(id);
}


int Scene::CreateEntity()
{
	m_entities++;
	return m_entities;
}

void Scene::DeleteEntity(Entity id)
{
	m_entities--;
	m_transforms.RemoveComponent(id);
	m_sprites.RemoveComponent(id);
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = 0;
	
	for (int i = 0; i < 5; i++)
	{
		int ent = CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(250*(i+1), 250);
		tf.scale = Vector2(0.25f, 0.25f);
		m_transforms.AddComponent(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 2, 2, i);
		m_sprites.AddComponent(ent, sp);
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