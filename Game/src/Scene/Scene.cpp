#include <stdafx.h>

#include "Scene.h"


Scene::Scene() :
	m_entities(0),
	m_sprites(), m_transforms(), 
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
	m_transforms.RemoveComponent(id);
	m_sprites.RemoveComponent(id);
}


void Scene::Init()
{
	std::cout << "Scene initialized." << std::endl;
	m_entities = 0;
	
	CreateComponentArray<Transform>();

	for (int i = 0; i < 50; i++)
	{
		int ent = CreateEntity();

		Transform tf = Transform();
		tf.position = Vector2(20.0f*(i+1), 250.0f);
		tf.velocity = Vector2(0.0f, 50.0f);
		tf.scale = Vector2(0.25f, 0.25f);
		m_transforms.AddComponent(ent, tf);

		Sprite sp = Sprite(".//res//jonathan.bmp", 1, 1);
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


Transform& Scene::GetTransform(Entity id)
{
	return m_transforms.GetComponent(id);
}

Sprite& Scene::GetSprite(Entity id)
{
	return m_sprites.GetComponent(id);
}


template <typename T>
T& Scene::GetComponent(Entity id)
{
	// If the component array is not already created...
	if (m_componentArrays.find(typename(T) == m_componentArrays.end()))
		CreateComponentArray<T>();
	
	std::shared_ptr<ComponentArray<T>> arr = m_componentArrays[typename(T)];
	return arr->GetComponent(id);
}


template <typename T>
void Scene::CreateComponentArray()
{
	const std::type_info& typeName = typeid(T);
	assert("Component array already exists" && m_componentArrays.find(typeName) == m_componentArrays.end());

	m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	m_componentTypes.insert({ typeName, m_typeCount });
	m_typeCount++;
}