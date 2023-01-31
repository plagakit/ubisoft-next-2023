#pragma once

#include <stdafx.h>

#include "Components/ComponentArray.h"
#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"

#include "Systems/RenderSystem/RenderSystem.h"

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 1000;

class Scene {

public:
	void Init();
	void Update(float deltaTime);
	void Render();
	
	Transform GetTransform(Entity id) const;
	//void SetTransform(Entity id, Transform transform);

	//Sprite GetSprite(Entity id) const;
	//void SetSprite(Entity id, Sprite sprite);

	int CreateEntity();
	void DeleteEntity(Entity id);

private:
	int entities;

	ComponentArray<Sprite> sprites;
	ComponentArray<Transform> transforms;

	RenderSystem render_system;

};