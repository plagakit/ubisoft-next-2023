#pragma once

#include <stdafx.h>

#include "Camera/Camera.h"
#include "Core/ContiguousArray/ContiguousArray.h"
#include "Core/Signal/Signal.h"
#include "UI/UI.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"
#include "Systems/TimerSystem/TimerSystem.h"
#include "Systems/PlayerSystem/PlayerSystem.h"
#include "Systems/BombSystem/BombSystem.h"
#include "Systems/ParticleSystem/ParticleSystem.h"
#include "Systems/HealthSystem/HealthSystem.h"
#include "Systems/ZombieSystem/ZombieSystem.h"

class Scene {

public:
	static const Entity MAX_ENTITIES = 10000;
	static const Entity NULL_ENTITY = 0;
	float m_deltaTime = 0;

	Signal<> s_EntityDeleted;

	// Scene methods

	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();

	// Entity methods

	Entity GetCount();

	Signature GetSignature(Entity id);

	bool DoesEntityExist(Entity id);

	template <typename... Components>
	std::vector<Entity> GetEntities();
	
	Entity CreateEntity();

	void DeleteEntity(Entity id);

	void QueueDelete(Entity id);

	void DeleteQueuedEntities();

	// TODO: Remove this method! (replace with something better)
	float AvailableEntitiesPercent();


	// Component methods

	template <typename T>
	bool IsComponentArrayCreated();

	template <typename T>
	void CreateComponentArray();

	template <typename T>
	std::shared_ptr<ContiguousArray<T>> GetComponentArray();

	template <typename T>
	ComponentID GetComponentType();

	template <typename T>
	bool HasComponent(Entity id);

	template <typename T>
	T GetComponent(Entity id);

	template <typename T>
	void SetComponent(Entity id, T component);

	template <typename T>
	void AddComponent(Entity id, T component);

	template <typename T>
	void RemoveComponent(Entity id);

	// Misc methods

	Camera GetCamera();


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
	ParticleSystem m_particleSystem;
	PlayerSystem m_playerSystem;
	BombSystem m_bombSystem;
	HealthSystem m_healthSystem;
	ZombieSystem m_zombieSystem;

	// Misc
	Camera m_camera;
	UI m_ui;

	// Gameplay
	const float MAP_BOUNDS_X = 1000.0f;
	const float MAP_BOUNDS_Y = 1000.0f;
	const float MAP_BOUND_WIDTH = 300.0f;
	const float MAP_LONG_WIDTH = MAP_BOUND_WIDTH + MAP_BOUNDS_X * 2;
	const float MAP_LONG_HEIGHT = MAP_BOUND_WIDTH + MAP_BOUNDS_Y * 2;

	Entity m_player;

	const float RESTART_SCENE_TIME = 3.0f;
	Timer restartSceneTimer;

	Entity CreateWall(Vector2 pos, float width, float height);

};


// Templated entity methods

template <typename... Components>
std::vector<Entity> Scene::GetEntities()
{
	// GetEntities<>() returns every entity
	if (sizeof...(Components) == 0)
		return m_entities;

	// Unpack variadic template into a list of component types, ignoring first
	ComponentID types[] = { 0, GetComponentType<Components>()... };

	// Set the signature's bits based on types array
	Signature mask;
	for (int i = 1; i < (sizeof...(Components) + 1); i++)
		mask.set(types[i]);


	// Copy any signature that has at least the component mask's bits (has required components) into a vector
	auto matchPred = [this, mask](Entity id) { 
		return (m_signatures.Get(id) & mask) == mask;
	};

	std::vector<Entity> matches;
	std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(matches), matchPred);

	return matches;
}


// Templated component methods

template<typename T>
bool Scene::IsComponentArrayCreated()
{
	return m_componentTypes.find(typeid(T)) != m_componentTypes.end();
}

template <typename T>
void Scene::CreateComponentArray()
{
	const std::type_info& type = typeid(T);

	m_componentArrays[type] = std::make_shared<ContiguousArray<T>>();
	m_componentTypes[type] = m_typeCount;

	// Add the remove component function to map so that it can be used @ runtime w/ ComponentID
	auto rmFunc = Delegate<Entity>();
	rmFunc.Bind<Scene, &Scene::RemoveComponent<T>>(this);
	m_removeComponentFunctions[m_typeCount] = rmFunc;

	m_typeCount++;
}

template <typename T>
std::shared_ptr<ContiguousArray<T>> Scene::GetComponentArray()
{
	//assert("Component array doesn't exist!" && IsComponentArrayCreated<T>());
	const auto& type = typeid(T);
	return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[type]);
}

template <typename T>
ComponentID Scene::GetComponentType()
{
	const std::type_info& type = typeid(T);
	//auto find = m_componentTypes.find(type);
	//assert("Component array doesn't exist!" && find != m_componentTypes.end());
	//return find->second;
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
T Scene::GetComponent(Entity id)
{
	return GetComponentArray<T>()->Get(id);
}

template <typename T>
void Scene::SetComponent(Entity id, T component)
{
	GetComponentArray<T>()->Set(id, component);
}

template <typename T>
void Scene::AddComponent(Entity id, T component)
{
	if (!IsComponentArrayCreated<T>())
		CreateComponentArray<T>();
	
	GetComponentArray<T>()->Add(id, component);
	m_signatures.Set(id, m_signatures.Get(id).set(GetComponentType<T>()));
}

template <typename T>
void Scene::RemoveComponent(Entity id)
{
	GetComponentArray<T>()->Remove(id);
	m_signatures.Set(id, m_signatures.Get(id).reset(GetComponentType<T>()));
}