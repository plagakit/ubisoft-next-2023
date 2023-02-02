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
	
}

void Scene::Update(float deltaTime)
{	
	for (int id = 1; id <= m_entities; id++)
		m_physicsSystem.UpdatePosition(id, deltaTime);	
}

void Scene::Render()
{
	for (int id = 1; id <= m_entities; id++)
		m_renderSystem.Render(id);
}