#pragma once

#include <stdafx.h>

class Scene;
class EntityManager;
struct Camera;

class RenderSystem {

public:
	void Render(Scene& scene);

private:
	void RenderSprite(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);

};