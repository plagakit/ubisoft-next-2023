#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	entities(0), sprites(), transforms(), render_system(this), physics_system(this)
{}

Transform& Scene::GetTransform(Entity id)
{
	return transforms.GetComponent(id);
}

Sprite& Scene::GetSprite(Entity id)
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
	
	for (int i = 0; i < 5000; i++) {
		int ent = CreateEntity();
		
		Transform tf = Transform();
		tf.position = Vector2(std::rand() % 1000, std::rand()%1000);
		tf.velocity = Vector2(cosf(rand()) * 0.05f, sinf(rand()) * 0.05f);
		transforms.AddComponent(ent, tf);

		Sprite s = Sprite(".\\res\\Test.bmp", 8, 4);
		sprites.AddComponent(ent, s);
	}

	std::cout << transforms.GetSize();
}

void Scene::Update(float deltaTime)
{
	for (int id = 1; id < entities; id++)
		physics_system.UpdatePosition(id, deltaTime);
}

void Scene::Render()
{
	for (int id = 1; id < entities; id++)
		render_system.Render(id);
}