#pragma once

#include <stdafx.h>

#include "Components/ComponentArray/ComponentArray.h"
#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"


const Entity MAX_ENTITIES = 1000;
const ComponentType MAX_COMPONENT_TYPES = 32;
using Signature = std::bitset<MAX_COMPONENT_TYPES>();


class Scene {

public:
	float m_deltaTime = 0;

	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();

	int CreateEntity();
	void DeleteEntity(Entity id);


	template <typename T>
	void CreateComponentArray()
	{
		const std::type_info& typeName = typeid(T);
		assert("Component array already exists." && m_componentTypes.find(typeName) == m_componentTypes.end());

		m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
		m_componentTypes.insert({ typeName, m_typeCount });
		m_typeCount++;
	}

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const std::type_info& typeName = typeid(T);
		assert("Component array doesn't exist." && m_componentTypes.find(typeName) != m_componentTypes.end());

		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
	}

	template <typename T>
	T& GetComponent(Entity id)
	{
		// If the component array is not already created...
		if (m_componentTypes.find(typeid(T)) == m_componentTypes.end())
		{
			CreateComponentArray<T>();
		}

		return GetComponentArray<T>()->GetComponent(id);
	}

	template <typename T>
	void AddComponent(Entity id, T component)
	{
		assert("Component array not found when adding component" && m_componentTypes.find(typeid(T)) != m_componentTypes.end());
		assert("Entity doesn't exist" && id <= entities);
		GetComponentArray<T>()->AddComponent(id, component);
	}

private:
	int m_entities;
	std::vector<Signature> m_signatures;

	ComponentType m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentType> m_componentTypes;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;

	//template<typename T>
	//void CreateComponentArray();

	//template<typename T>
	//std::shared_ptr<ComponentArray<T>> GetComponentArray();

};