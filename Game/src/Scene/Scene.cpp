#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	entities(0), sprites(), transforms(), render_system(this)
{}

Transform Scene::GetTransform(Entity id)
{
	return transforms.GetComponent(id);
}

Sprite Scene::GetSprite(Entity id)
{
	return sprites.GetComponent(id);
}


int Scene::CreateEntity()
{
	entities++;
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
	std::srand(std::time(nullptr));

	entities = 0;
	
	for (int i = 0; i < 1000; i++) {
		int ent = CreateEntity();
		
		Transform tf = Transform();
		tf.position = Vector2(std::rand() % 1000, std::rand()%1000);
		transforms.AddComponent(ent, tf);


		sprites.AddComponent(ent, Sprite(60, 60, 0, 1, 0));
	}

	std::cout << transforms.GetSize();
}

void Scene::Update(float deltaTime)
{

}

void Scene::Render()
{
	std::string s = "";
	for (auto const& pair : transforms.entity_map)
		s += "{" + std::to_string(pair.first) + ", " + std::to_string(pair.second) + "} ";

	App::Print(0, 500, s.c_str(), 1, 1, 1);
	
	for (int id = 1; id < entities; id++)
		render_system.Render(id);
}