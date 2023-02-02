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
	
}

void Scene::Update(float deltaTime)
{
	dt = deltaTime / 60;
	
	for (int i = 0; i < 5; i++)
	{
		int ent = CreateEntity();
		Transform tf = Transform();
		tf.position = Vector2(512, 512);
		tf.velocity = Vector2(cosf(rand()) * 10, (sinf(rand()) + 1) / 2.0f * 15 + 5);
		tf.scale = Vector2(0.25f, 0.25f);
		transforms.AddComponent(ent, tf);
		Sprite s = Sprite(".\\res\\jonathan.bmp", 1, 1);
		sprites.AddComponent(ent, s);
	}
	
	for (int id = 1; id <= entities; id++)
		physics_system.UpdatePosition(id, deltaTime);

	
}

void Scene::Render()
{
	App::Print(200, 200, std::to_string(dt).c_str());
	for (int id = 1; id <= entities; id++)
		render_system.Render(id);
}