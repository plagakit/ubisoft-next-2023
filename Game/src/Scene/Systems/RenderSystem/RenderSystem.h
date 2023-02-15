#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

struct Camera;
class EntityManager;

class RenderSystem : public ISystem {
	using ISystem::ISystem;

private:
	void Render(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);

public:
	void Update(Scene& scene);

};