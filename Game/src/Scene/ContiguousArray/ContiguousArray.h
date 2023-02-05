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

	std::string ToString();
	
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
	assert("Get: entity not found in map." && m_entityMap.find(id) != m_entityMap.end());
	auto itemIndex = m_entityMap.find(id);
	return m_items[itemIndex->first];
}

template<typename T>
void ContiguousArray<T>::Add(Entity id, T item)
{
	// TODO: add assert
	m_items.push_back(item);
	m_entityMap.insert({ id, m_numItems });
	m_numItems++;
}

template<typename T>
void ContiguousArray<T>::Remove(Entity id)
{
	assert(("Remove: entity not found in map.") && m_entityMap.find(id) != m_entityMap.end());

	// Swap memory of deleted component and last component in vector
	m_numItems--;
	int removedIndex = m_entityMap[id];

	m_entityMap[id] = m_entityMap[m_numItems];
	m_entityMap.erase(m_numItems);

	std::swap(m_items[removedIndex], m_items.back());
	m_items.pop_back();
}

/*
template <typename T>
int ComponentArray<T>::GetSize() const
{
	return m_activeComponents;
}
*/

template <typename T>
std::string ContiguousArray<T>::ToString()
{
	std::string str = "";
	for (auto const& pair : m_entityMap)
		str += "{" + std::to_string(pair.first) + ": " + std::to_string(pair.second) + "} ";
	return str;
}

template class ContiguousArray<Signature>;
template class ContiguousArray<Transform>;
template class ContiguousArray<Sprite>;
