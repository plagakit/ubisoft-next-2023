#pragma once

#include <stdafx.h>

#include <Scene/ContiguousArray/ContiguousArray.h>


class ComponentManager {

public:

	template <typename T>
	void CreateArray()
	{
		const std::type_info& typeName = typeid(T);
		assert("Component array already exists." && m_componentTypes.find(typeName) == m_componentTypes.end());

		m_componentArrays.insert({ typeName, std::make_shared<ContiguousArray<T>>() });
		m_componentTypes.insert({ typeName, m_typeCount });
		m_typeCount++;
	}

	template <typename T>
	std::shared_ptr<ContiguousArray<T>> GetArray()
	{
		const std::type_info& typeName = typeid(T);
		assert("Component array doesn't exist." && m_componentTypes.find(typeName) != m_componentTypes.end());

		return std::static_pointer_cast<ContiguousArray<T>>(m_componentArrays[typeName]);
	}

	template <typename T>
	T& GetComponent(Entity id)
	{
		return GetArray<T>()->Get(id);
	}

	template <typename T>
	void AddComponent(Entity id, T component)
	{
		assert("Entity doesn't exist" && id <= entities);

		// If the component array is not already created...
		if (m_componentTypes.find(typeid(T)) == m_componentTypes.end())
		{
			CreateArray<T>();
		}

		GetArray<T>()->Add(id, component);
	}

	template <typename T>
	void RemoveComponent(Entity id)
	{
		assert("Entity doesn't exist" && id <= entities);
		GetArray<T>()->Remove(id);
	}

private:
	ComponentType m_typeCount = 0;
	std::unordered_map<std::type_index, std::shared_ptr<IContiguousArray>> m_componentArrays;
	std::unordered_map<std::type_index, ComponentType> m_componentTypes;

};