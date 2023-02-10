#include <stdafx.h>

#include "EntityManager.h"


EntityManager::EntityManager() :
	m_count(0), MAX_ENTITIES(1000)
{}

void EntityManager::Init()
{
	m_count = 0;
	m_entities.clear();
	m_availableEntities = {};

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push(i);
}

std::vector<Entity> EntityManager::GetEntities()
{
	return m_entities;
}

Entity EntityManager::GetCount()
{
	return m_count;
}

Entity EntityManager::CreateEntity()
{
	assert("Ran out of entities!" && m_availableEntities.size() > 0);

	Entity id = m_availableEntities.front();
	m_availableEntities.pop();
	m_entities.push_back(id);
	m_count++;

	return id;
}

void EntityManager::DeleteEntity(ComponentManager& componentMgr, Entity id)
{
	m_count--;

	auto ent = std::find(m_entities.begin(), m_entities.end(), id);
	assert("Entity not found in vector!" && ent != m_entities.end());

	m_entities.erase(ent);
	/*componentMgr.RemoveComponent<Transform>(id);
	componentMgr.RemoveComponent<Sprite>(id);
	componentMgr.RemoveComponent<Timer>(id);*/
}