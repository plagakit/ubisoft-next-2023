#pragma once

#include <stdafx.h>

class Scene;
class EntityManager;
struct Camera;
struct Vector2;
struct Transform;

class RenderSystem {

public:
	void Render(Scene& scene);

private:
	void RenderSprite(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderPhysicsBounds(Camera& camera, EntityManager& entityMgr);

	void DrawWireframe(Camera& camera, Transform& transform, std::vector<Vector2>& points, float r = 1.0f, float g = 1.0f, float b = 1.0f);

};