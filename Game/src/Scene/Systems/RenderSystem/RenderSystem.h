#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

struct Camera;
class EntityManager;

class RenderSystem : public ISystem {

public:
	void Update(Scene& scene);

private:
	void Render(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);

};