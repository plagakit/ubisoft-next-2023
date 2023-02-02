#pragma once

#include <stdafx.h>

#include "Components/ComponentArray.h"
#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 1000;

/* Because the game is only one scene, there are no entity managers,
* component managers, or system managers. If the scope of the game was bigger,
* there would definitely be managers of these types that involve templates and
* stuff like that, but just because the game is small and there's one scene
* I'm shoving every ECS-related thing into this class.
*/
class Scene {

public:
	Scene();
	void Init();
	void Update(float deltaTime);
	void Render();

	Transform& GetTransform(Entity id);
	//void SetTransform(Entity id, Transform transform);

	Sprite& GetSprite(Entity id);
	//void SetSprite(Entity id, Sprite sprite);

	int CreateEntity();
	void DeleteEntity(Entity id);

private:
	float m_deltaTime;

	int m_entities;

	ComponentArray<Sprite> m_sprites;
	ComponentArray<Transform> m_transforms;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;

};