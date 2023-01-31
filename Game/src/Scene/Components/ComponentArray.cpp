#include <stdafx.h>

#include "ComponentArray.h"

template<typename T> 
ComponentArray<T>::ComponentArray<T>() 
	: components(), entity_map(), active_entities(0)
{}

template<typename T>
T ComponentArray<T>::GetComponent(Entity id) const
{
	// TODO: add assert
	return components[entity_map.find(id)];
}

template<typename T>
void ComponentArray<T>::AddComponent(Entity id, T component) 
{
	// TODO: add assert
	active_entities++;
	components.push_back(component);
	entity_map.insert(id, active_entities);
}

template<typename T>
void ComponentArray<T>::RemoveComponent(Entity id) 
{
	// TODO: add assert

	active_entities--;

	int removed_index = entity_map[id];
	components[removed_index] = components[active_entities];

	components.erase(active_entities);
	entity_map.erase(active_entities);
}

void TempFunction()
{
	ComponentArray<int> temp_object;
}