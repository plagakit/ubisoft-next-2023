#include <stdafx.h>

#include "EntityManager.h"


EntityManager::EntityManager(Entity MAX_ENTS) :
	m_count(0), MAX_ENTITIES(MAX_ENTS)
{}

void EntityManager::Init()
{
	m_count = 0;
	m_entities.clear();
	m_availableEntities = {};

	for (Entity i = 0; i < MAX_ENTITIES; i++)
		m_availableEntities.push(i);
}

//std::vector<Entity> EntityManager::GetEntities()
//{
//	return m_entities;
//}

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
	m_signatures.Add(id, Signature());
	m_count++;

	return id;
}

void EntityManager::DeleteEntity(Entity id)
{
	m_count--;

	auto ent = std::find(m_entities.begin(), m_entities.end(), id);
	assert("Entity not found in vector!" && ent != m_entities.end());

	m_entities.erase(ent);
	m_availableEntities.push(id);

	// For each component type in the signature, call its remove function!
	Signature& signature = m_signatures.Get(id);
	for (auto i = 0; i < signature.size(); i++)
		if (signature.test(i))
			m_removeDelegates[i](id);
}

bool EntityManager::HasEntity(Entity id)
{
	return std::find(m_entities.begin(), m_entities.end(), id) != m_entities.end();
}

void EntityManager::QueueDelete(Entity id)
{
	if (std::find(m_deleteQueue.begin(), m_deleteQueue.end(), id) == m_deleteQueue.end())
		m_deleteQueue.push_back(id);
}

void EntityManager::DeleteQueuedEntities()
{
	while (!m_deleteQueue.empty())
	{
		Entity id = m_deleteQueue.front();
		DeleteEntity(id);
		m_deleteQueue.pop_front();
	}
}