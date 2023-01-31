#include <stdafx.h>

#include "Scene.h"


Transform Scene::GetTransform(Entity id) const
{
	return transforms.GetComponent(id);
}

int Scene::CreateEntity()
{
	entities++;

	transforms.AddComponent(entities, Transform());
	sprites.AddComponent(entities, Sprite());

	return entities;
}

void Scene::DeleteEntity(Entity id)
{
	entities--;
	transforms.RemoveComponent(id);
	sprites.RemoveComponent(id);
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;

	entities = 0;
}

void Scene::Update(float deltaTime)
{

}

void Scene::Render()
{

}