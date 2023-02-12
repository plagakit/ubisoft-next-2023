#pragma once

#include <stdafx.h>

#include <Scene/ContiguousArray/ContiguousArray.h>

class ComponentManager {

public:
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
	ComponentID m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IContiguousArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentID> m_componentTypes;

};

template <typename T>
void ComponentManager::CreateComponentArray()
{
	const std::type_info& typeName = typeid(T);
	assert("CreateComponentArray: Component array already exists." && m_componentTypes.find(typeName) == m_componentTypes.end());

	m_componentArrays.insert({ typeName, std::make_shared<ContiguousArray<T>>() });
	m_componentTypes.insert({ typeName, m_typeCount });
	m_typeCount++;
}

template <typename T>
std::shared_ptr<ContiguousArray<T>> ComponentManager::GetComponentArray()
{
	const std::type_info& typeName = typeid(T);
	assert("GetComponentArray: Component array doesn't exist." && m_componentTypes.find(typeName) != m_componentTypes.end());

	return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[typeName]);
}

template <typename T>
T& ComponentManager::GetComponent(Entity id)
{
	return GetComponentArray<T>()->Get(id);
}

template <typename T>
void ComponentManager::AddComponent(Entity id, T component)
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
void ComponentManager::RemoveComponent(Entity id)
{
	// TODO: Add assert
	GetComponentArray<T>()->Remove(id);
}