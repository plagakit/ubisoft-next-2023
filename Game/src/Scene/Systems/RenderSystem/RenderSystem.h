#pragma once

#include <stdafx.h>

#include "Scene/Systems/Signal/Signal.h"

class Scene;
struct Camera;
class EntityManager;

class RenderSystem {

public:
	void Render(Scene& scene);
	void test(Entity e) { ids += std::to_string(e) + " "; }

private:
	void RenderSprite(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);


	std::string ids;
	

};