#include <stdafx.h>

#include "Scene.h"


Transform Scene::GetTransform(int id) const 
{
	return transforms[id];
}

void Scene::SetTransform(int id, Transform transform)
{
	transforms[id] = transform;
}

Sprite Scene::GetSprite(int id) const
{
	return sprites[id];
}

void Scene::SetSprite(int id, Sprite sprite)
{
	sprites[id] = sprite;
}


int Scene::CreateEntity()
{
	entities++;

	transforms.push_back(Transform());
	sprites.push_back(Sprite());

	return entities;
}

void Scene::DeleteEntity(int id)
{
	

}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;

	entities = 0;
}

void Scene::Update(float deltaTime)
{
	for (int i = 0; i < transforms.size()) {

	}
}

void Scene::Render()
{

}