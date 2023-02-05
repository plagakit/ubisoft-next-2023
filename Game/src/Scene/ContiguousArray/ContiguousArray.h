#pragma once

#include <stdafx.h>

#include "IContiguousArray.h"
#include <Scene/Components/Sprite/Sprite.h>
#include <Scene/Components/Transform/Transform.h>

template<typename T>
class ContiguousArray : public IContiguousArray {

public:
	ContiguousArray();

	T& Get(Entity id);
	//int GetSize() const;

	void Add(Entity id, T component);
	void Remove(Entity id);

	
private:
	std::vector<T> m_items;
	std::unordered_map<Entity, int> m_entityMap;
	int m_numItems;

};


template<typename T>
ContiguousArray<T>::ContiguousArray()
	: m_items(), m_entityMap(), m_numItems(0)
{}

template<typename T>
T& ContiguousArray<T>::Get(Entity id)
{
	// TODO: add assert
	auto itemIndex = m_entityMap.find(id);
	return m_items[itemIndex->first-1];
}

template<typename T>
void ContiguousArray<T>::Add(Entity id, T item)
{
	// TODO: add assert
	m_items.push_back(item);
	m_entityMap[id] = m_numItems;
	m_numItems++;
}

template<typename T>
void ContiguousArray<T>::Remove(Entity id)
{
	// TODO: add assert

	// Swap memory of deleted component and last component in vector
	int removed_index = m_entityMap[id];
	m_items[removed_index] = m_items[m_numItems];

	m_items.erase(m_items.begin() + m_numItems);
	m_entityMap.erase(m_numItems);

	m_numItems--;
}

/*
template <typename T>
int ComponentArray<T>::GetSize() const
{
	return m_activeComponents;
}
*/

template class ContiguousArray<Signature>;
template class ContiguousArray<Transform>;
template class ContiguousArray<Sprite>;
