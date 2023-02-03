#pragma once

#include <stdafx.h>

#include "IComponentArray.h"
#include <Scene/Components/Sprite/Sprite.h>
#include <Scene/Components/Transform/Transform.h>

template<typename T>
class ComponentArray : public IComponentArray {

public:
	ComponentArray();

	T& GetComponent(Entity id);
	//int GetSize() const;

	void AddComponent(Entity id, T component);
	void RemoveComponent(Entity id);

	
private:
	std::vector<T> m_components;
	std::unordered_map<Entity, int> m_entityMap;
	int m_activeComponents;

};


template<typename T>
ComponentArray<T>::ComponentArray()
	: m_components(), m_entityMap(), m_activeComponents(0)
{}

template<typename T>
T& ComponentArray<T>::GetComponent(Entity id)
{
	// TODO: add assert
	auto componentIndex = m_entityMap.find(id);
	return m_components[componentIndex->first - 1]; // index starts at 1
}

template<typename T>
void ComponentArray<T>::AddComponent(Entity id, T component)
{
	// TODO: add assert
	m_activeComponents++;
	m_components.push_back(component);
	m_entityMap[id] = m_activeComponents;
}

template<typename T>
void ComponentArray<T>::RemoveComponent(Entity id)
{
	// TODO: add assert

	m_activeComponents--;

	// Swap memory of deleted component and last component in vector
	int removed_index = m_entityMap[id];
	m_components[removed_index] = m_components[m_activeComponents];

	m_components.erase(m_components.begin() + m_activeComponents);
	m_entityMap.erase(m_activeComponents);
}

/*
template <typename T>
int ComponentArray<T>::GetSize() const
{
	return m_activeComponents;
}
*/

template class ComponentArray<Transform>;
template class ComponentArray<Sprite>;
