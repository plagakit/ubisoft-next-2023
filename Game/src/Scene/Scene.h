#pragma once

#include <stdafx.h>

#include "Components/Transform/Transform.h"


using ComponentType = std::uint8_t;
using Entity = std::uint32_t;

const ComponentType MAX_COMPONENT_TYPES = 32;
const int MAX_ENTITIES = 100;


class Scene {

public:
	void Init();
	void Update(float deltaTime);
	void Render();
	
	Transform GetTransform(int id) const;
	void SetTransform(int id, Transform transform);

private:
	Entity entities[MAX_ENTITIES];
	Transform transforms[MAX_ENTITIES];

};