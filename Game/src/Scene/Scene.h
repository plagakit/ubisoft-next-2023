#pragma once

#include <stdafx.h>

#include "Camera/Camera.h"
#include "Core/ContiguousArray/ContiguousArray.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"
#include "Systems/TimerSystem/TimerSystem.h"
#include "Systems/PlayerSystem/PlayerSystem.h"

class Scene {

public:
	const Entity MAX_ENTITIES = 1000;
	float m_deltaTime = 0;

	Scene();

	// Scene methods

	void Init();
	void Update(float deltaTime);
	void Render();


	// Entity methods

	Entity GetCount();

	bool DoesEntityExist(Entity id);

	template <typename... Components>
	std::vector<Entity> GetEntities();
	
	Entity CreateEntity();

	void DeleteEntity(Entity id);

	void QueueDelete(Entity id);

	void DeleteQueuedEntities();


	// Component methods

	template <typename T>
	void CreateComponentArray();

	template <typename T>
	std::shared_ptr<ContiguousArray<T>> GetComponentArray();

	template <typename T>
	ComponentID GetComponentType();

	template <typename T>
	bool HasComponent(Entity id);

	template <typename T>
	T& GetComponent(Entity id);

	template <typename T>
	void AddComponent(Entity id, T component);

	template <typename T>
	void RemoveComponent(Entity id);


	// Misc methods

	Camera& GetCamera();


private:
	// Entities
	Entity m_count;
	std::vector<Entity> m_entities;
	ContiguousArray<Signature> m_signatures;

	std::deque<Entity> m_availableEntities;
	std::deque<Entity> m_deleteQueue;

	// Components
	ComponentID m_typeCount = 0;
	std::unordered_map<std::type_index, ComponentID> m_componentTypes;
	std::unordered_map<std::type_index, std::shared_ptr<IContiguousArray>> m_componentArrays;

	/* Contiguous arrays are template classes - generated at compile time.
	*  Remove function is used at runtime - see DeleteEntity() in Scene.cpp.
	*  Keeping a map to the remove functions ensures we can use each specific 
	*  implementation of the template function at runtime when given a ComponentID. 
	*  Delegates are assigned when the component array is created.
	*/
	std::unordered_map<ComponentID, Delegate<Entity>> m_removeComponentFunctions;

	// Systems
	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;
	TimerSystem m_timerSystem;
	PlayerSystem m_playerSystem;

	// Misc
	Camera m_camera;

};


// Templated entity methods

template <typename... Components>
std::vector<Entity> Scene::GetEntities()
{
	// GetEntities<>() returns every entity
	if (sizeof...(Components) == 0)
		return m_entities;

	// Unpack variadic template into a list of component types
	ComponentID types[] = { 0, GetComponentType<Components>()... };

	// Set the signature's bits based on types array
	Signature mask;
	for (int i = 1; i < (sizeof...(Components) + 1); i++)
		mask.set(types[i]);

	// Copy any signature that matches the component mask (has required components) into a vector
	std::vector<Entity> matches;
	std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(matches),
		[this, &mask](Entity id) { return (m_signatures.Get(id) & mask) == mask; });

	return matches;
}


// Templated component methods

template <typename T>
void Scene::CreateComponentArray()
{
	const std::type_info& type = typeid(T);

	m_componentArrays.insert({ type, std::make_shared<ContiguousArray<T>>() });
	m_componentTypes.insert({ type, m_typeCount });

	// Add the remove component function to map so that it can be used @ runtime w/ ComponentID
	auto rmFunc = Delegate<Entity>();
	rmFunc.Bind<Scene, &Scene::RemoveComponent<T>>(this);
	m_removeComponentFunctions.insert({ m_typeCount, rmFunc });

	m_typeCount++;
}

template <typename T>
std::shared_ptr<ContiguousArray<T>> Scene::GetComponentArray()
{
	const auto& type = typeid(T);
	return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[type]);
}

template <typename T>
ComponentID Scene::GetComponentType()
{
	const std::type_info& type = typeid(T);
	return m_componentTypes[type];
}

template <typename T>
bool Scene::HasComponent(Entity id)
{
	Signature& signature = m_signatures.Get(id);
	ComponentID componentID = GetComponentType<T>();
	return signature.test(componentID);
}

template <typename T>
T& Scene::GetComponent(Entity id)
{
	return GetComponentArray<T>()->Get(id);
}

template <typename T>
void Scene::AddComponent(Entity id, T component)
{
	GetComponentArray<T>()->Add(id, component);
	m_signatures.Get(id).set(GetComponentType<T>());
}

template <typename T>
void Scene::RemoveComponent(Entity id)
{
	GetComponentArray<T>()->Remove(id);
	m_signatures.Get(id).reset(GetComponentType<T>());
}