#pragma once

#include <stdafx.h>

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
	
	Transform GetTransform(int id) const;
	void SetTransform(int id, Transform transform);

	Sprite GetSprite(int id) const;
	void SetSprite(int id, Sprite sprite);

	int CreateEntity();
	void DeleteEntity(int id);

private:
	int entities;

	std::vector<Sprite> sprites;
	std::vector<Transform> transforms;

	RenderSystem render_system;

};