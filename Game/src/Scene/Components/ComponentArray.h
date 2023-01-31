#pragma once

#include <stdafx.h>

template<typename T>
class ComponentArray {

public:
	ComponentArray();

	T GetComponent(Entity id) const;
	void AddComponent(Entity id, T component);
	void RemoveComponent(Entity id);
	

private:
	std::vector<T> components;
	std::unordered_map<Entity, int> entity_map;
	int active_entities;

};