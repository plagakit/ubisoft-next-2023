#pragma once

#include <stdafx.h>

#include "Sprite/Sprite.h"
#include "Transform/Transform.h"

template<typename T>
class ComponentArray {

public:
	ComponentArray();
	T GetComponent(Entity id);
	void AddComponent(Entity id, T component);
	void RemoveComponent(Entity id);
	
private:
	std::vector<T> components;
	std::unordered_map<Entity, int> entity_map;
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
	auto component_index = entity_map.find(id);
	assert(component_index != entity_map.end());
	return components[component_index->first];
}


template<typename T>
void ComponentArray<T>::AddComponent(Entity id, T component)
{
	// TODO: add assert
	active_entities++;
	components.push_back(component);
	entity_map.insert({id, active_entities});
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

template class ComponentArray<Transform>;
template class ComponentArray<Sprite>;
