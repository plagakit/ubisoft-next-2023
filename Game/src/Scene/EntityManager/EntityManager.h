#pragma once

#include <stdafx.h>

#include <Scene/Components/ComponentManager.h>

class EntityManager {

public:

	EntityManager();

	void Init();

	// CHANGE EVENTUALLY
	std::vector<Entity> GetEntities();

	Entity GetCount();

	Entity CreateEntity();
	void DeleteEntity(ComponentManager& componentMgr, Entity id);


private:
	const Entity MAX_ENTITIES;

	Entity m_count;
	std::vector<Entity> m_entities;
	std::queue<Entity> m_availableEntities;

};