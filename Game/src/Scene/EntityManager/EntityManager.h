#pragma once

#include <stdafx.h>

#include "Scene/ContiguousArray/ContiguousArray.h"
#include "Core/Delegate/Delegate.h"

class EntityManager {

public:

	EntityManager(Entity MAX_ENTITIES);

	void Init();

	template <typename... Components>
	std::vector<Entity> GetEntities();

	

	void QueueDelete(Entity id);

	void DeleteQueuedEntities();
	

	template <typename T>
	void AddComponent(Entity id, T component);

	template <typename T>
	void RemoveComponent(Entity id);

	void DeleteEntity(Entity id);

};


