#pragma once

#include <stdafx.h>

#include <Scene/ContiguousArray/ContiguousArray.h>

class EntityManager {

public:

	EntityManager(Entity MAX_ENTITIES);

	void Init();

	template <typename... Components>
	std::vector<Entity> GetEntities();

	Entity GetCount();

	Entity CreateEntity();
	
	void DeleteEntity(Entity id);

	bool HasEntity(Entity id);

	template <typename T>
	void CreateComponentArray();

	template <typename T>
	std::shared_ptr<ContiguousArray<T>> GetComponentArray();

	template <typename T>
	ComponentID GetComponentType();

	template <typename T>
	T& GetComponent(Entity id);

	template <typename T>
	void AddComponent(Entity id, T component);

	template <typename T>
	void RemoveComponent(Entity id);

	void DeleteQueuedEntities();


private:
	const Entity MAX_ENTITIES;

	Entity m_count;
	std::vector<Entity> m_entities;
	std::queue<Entity> m_availableEntities;
	ContiguousArray<Signature> m_signatures;
	std::queue<Entity> m_deleteQueue;

	ComponentID m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IContiguousArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentID> m_componentTypes;
	

	/* Contiguous arrays are template classes - generated at compile time.
	*  Remove function is used at runtime - see DeleteEntity() in EntityManager.cpp.
	*  Keeping a map to function pointers ensures we can use each specific implementation
	*  of the template function at runtime when given a ComponentID. Function
	*  pointers are assigned when the component array is created.
	*/
	using ComponentArrayFunction = void (EntityManager::*)(Entity);
	std::unordered_map<ComponentID, ComponentArrayFunction> m_removeFunctions;

};


template <typename... Components>
std::vector<Entity> EntityManager::GetEntities()
{
	if (sizeof...(Components) == 0)
		return m_entities;
	
	// Unpack variadic template into a list of component types, and set the mask!
	ComponentID types[] = { 0, GetComponentType<Components>()... };
	Signature mask;
	for (int i = 1; i < (sizeof...(Components) + 1); i++)
	{
		const std::type_info& type = typeid(types[i]);
		mask.set(m_componentTypes[type]);
	}

	// Copies any matches for the component mask into the vector
	std::vector<Entity> matches;
	std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(matches),
		[this, &mask](Entity id) { return (m_signatures.Get(id) & mask) == mask; });

	return matches;
}


template <typename T>
void EntityManager::CreateComponentArray()
{
	const std::type_info& type = typeid(T);
	assert("CreateComponentArray: Component array already exists." && m_componentTypes.find(type) == m_componentTypes.end());
	assert("Max component types reached." && m_typeCount < MAX_COMPONENT_TYPES);

	m_componentArrays.insert({ type, std::make_shared<ContiguousArray<T>>() });
	m_componentTypes.insert({ type, m_typeCount });
	m_removeFunctions.insert({ m_typeCount, &EntityManager::RemoveComponent<T> });
	m_typeCount++;
}

template <typename T>
ComponentID EntityManager::GetComponentType()
{
	const std::type_info& type = typeid(T);
	return m_componentTypes[type];
}

template <typename T>
std::shared_ptr<ContiguousArray<T>> EntityManager::GetComponentArray()
{
	const std::type_info& type = typeid(T);
	assert("GetComponentArray: Component array doesn't exist." && m_componentTypes.find(type) != m_componentTypes.end());

	return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[type]);
}

template <typename T>
T& EntityManager::GetComponent(Entity id)
{
	return GetComponentArray<T>()->Get(id);
}

template <typename T>
void EntityManager::AddComponent(Entity id, T component)
{
	// TODO: Add assert

	// If the component array is not already created...
	if (m_componentTypes.find(typeid(T)) == m_componentTypes.end())
		CreateComponentArray<T>();

	GetComponentArray<T>()->Add(id, component);
	m_signatures.Get(id).set(GetComponentType<T>());
}

template <typename T>
void EntityManager::RemoveComponent(Entity id)
{
	// TODO: Add assert
	GetComponentArray<T>()->Remove(id);
	m_signatures.Get(id).reset(GetComponentType<T>());
}