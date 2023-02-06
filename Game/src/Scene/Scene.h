#pragma once

#include <stdafx.h>

#include "ContiguousArray/ContiguousArray.h"
#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"

#include "Systems/ISystem.h"
#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"


const Entity MAX_ENTITIES = 1000;

class Scene {

public:
	float m_deltaTime = 0;

	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();

	int CreateEntity();
	void DeleteEntity(Entity id);


	// COMPONENT ARRAY METHODS
	template <typename T>
	void CreateComponentArray();

	template <typename T>
	std::shared_ptr<ContiguousArray<T>> GetComponentArray();

	template <typename T>
	T& GetComponent(Entity id);

	template <typename T>
	void AddComponent(Entity id, T component);

	template <typename T>
	void RemoveComponent(Entity id);


private:
	Entity m_entities;
	ContiguousArray<Signature> m_signatures;

	ComponentType m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IContiguousArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentType> m_componentTypes;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;

	//template<typename T>
	//void CreateComponentArray();

	//template<typename T>
	//std::shared_ptr<ComponentArray<T>> GetComponentArray();

};

// Component array method implementations

template <typename T>
void Scene::CreateComponentArray()
{
	const std::type_info& typeName = typeid(T);
	assert("CreateComponentArray: Component array already exists." && m_componentTypes.find(typeName) == m_componentTypes.end());

	m_componentArrays.insert({ typeName, std::make_shared<ContiguousArray<T>>() });
	m_componentTypes.insert({ typeName, m_typeCount });
	m_typeCount++;
}

template <typename T>
std::shared_ptr<ContiguousArray<T>> Scene::GetComponentArray()
{
	const std::type_info& typeName = typeid(T);
	assert("GetComponentArray: Component array doesn't exist." && m_componentTypes.find(typeName) != m_componentTypes.end());

	return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[typeName]);
}

template <typename T>
T& Scene::GetComponent(Entity id)
{
	return GetComponentArray<T>()->Get(id);
}

template <typename T>
void Scene::AddComponent(Entity id, T component)
{
	// TODO: Add assert

	// If the component array is not already created...
	if (m_componentTypes.find(typeid(T)) == m_componentTypes.end())
	{
		CreateComponentArray<T>();
	}

	GetComponentArray<T>()->Add(id, component);
}

template <typename T>
void Scene::RemoveComponent(Entity id)
{
	// TODO: Add assert
	GetComponentArray<T>()->Remove(id);
}