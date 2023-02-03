#pragma once

#include <stdafx.h>

#include "Components/ComponentArray.h"
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

	Transform& GetTransform(Entity id);
	//void SetTransform(Entity id, Transform transform);

	Sprite& GetSprite(Entity id);
	//void SetSprite(Entity id, Sprite sprite);

	template<typename T>
	T& GetComponent(Entity id);

private:
	int m_entities;
	//std::vector<Signature> m_signatures;

	ComponentType m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentType> m_componentTypes;
	
	ComponentArray<Sprite> m_sprites;
	ComponentArray<Transform> m_transforms;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;

	template<typename T>
	void CreateComponentArray();

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray();

};