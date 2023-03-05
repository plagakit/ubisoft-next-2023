#pragma once

#include <stdafx.h>

#include "IContiguousArray.h"

template<typename T>
class ContiguousArray : public IContiguousArray {

public:
	ContiguousArray();

	T Get(Entity id);
	void Set(Entity id, T item);
	//int GetSize() const;

	void Add(Entity id, T item);
	void Remove(Entity id);	 

	std::string ToString();
	
private:
	std::vector<T> m_items;
	std::unordered_map<Entity, int> m_entityMap;
	std::unordered_map<int, Entity> m_indexMap;
 	int m_numItems;

};


template<typename T>
ContiguousArray<T>::ContiguousArray()
	: m_items(), m_entityMap(), m_indexMap(), m_numItems(0)
{}

template<typename T>
T ContiguousArray<T>::Get(Entity id)
{
	//auto itemIndex = m_entityMap.find(id);
	//assert("Get: entity not found in map." && itemIndex != m_entityMap.end());
	return m_items[m_entityMap[id]]; 
}

template <typename T>
void ContiguousArray<T>::Set(Entity id, T item)
{
	//auto itemIndex = m_entityMap.find(id);
	//assert("Get: entity not found in map." && itemIndex != m_entityMap.end());
	m_items[m_entityMap[id]] = item;
}

template<typename T>
void ContiguousArray<T>::Add(Entity id, T item)
{
	// TODO: add assert
	m_items.push_back(item);
	m_entityMap.insert({ id, m_numItems });
	m_indexMap.insert({ m_numItems, id });
	m_numItems++;
}

template<typename T>
void ContiguousArray<T>::Remove(Entity id)
{
	assert(("Remove: entity not found in map.") && m_entityMap.find(id) != m_entityMap.end());

	// Swap memory of deleted component and last component in vector
	m_numItems--;
	int removedIndex = m_entityMap[id];
	int lastID = m_indexMap[m_numItems];
	
	m_items[removedIndex] = m_items[m_numItems];
	m_entityMap[lastID] = removedIndex;
	m_indexMap[removedIndex] = lastID;
 
	m_items.pop_back();
	m_entityMap.erase(id);
	m_indexMap.erase(m_numItems);
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
