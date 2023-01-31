#pragma once

#include <stdafx.h>

#include "Sprite/Sprite.h"
#include "Transform/Transform.h"

template<typename T>
class ComponentArray {

public:
	ComponentArray();

	T GetComponent(Entity id);
	int GetSize() const;

	void AddComponent(Entity id, T component);
	void RemoveComponent(Entity id);

	std::unordered_map<Entity, int> entity_map;
	
private:
	std::vector<T> components;
	
	int active_entities;

};


template<typename T>
ComponentArray<T>::ComponentArray()
	: components(), entity_map(), active_entities(0)
{}

template<typename T>
T ComponentArray<T>::GetComponent(Entity id)
{
	// TODO: add assert
	std::cout << "TEST" << std::endl;
	auto component_index = entity_map.find(id);
	return components[component_index->first];
}

template<typename T>
void ComponentArray<T>::AddComponent(Entity id, T component)
{
	// TODO: add assert
	active_entities++;
	components.push_back(component);
	entity_map[id] = active_entities;
}

template<typename T>
void ComponentArray<T>::RemoveComponent(Entity id)
{
	// TODO: add assert

	active_entities--;

	int removed_index = entity_map[id];
	components[removed_index] = components[active_entities];

	components.erase(components.begin() + active_entities);
	entity_map.erase(active_entities);
}

template <typename T>
int ComponentArray<T>::GetSize() const
{
	return active_entities;
}

template class ComponentArray<Transform>;
template class ComponentArray<Sprite>;
