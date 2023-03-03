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
	void Test(Entity a) { test += "a"; }

private:
	void RenderSprite(Scene& scene, Entity id);
	void RenderWireframe(Scene& scene, Entity id);
	void RenderPhysicsBounds(Scene& scene);

	void DrawWireframe(Camera& camera, Transform& transform, std::vector<Vector2>& points, float r = 1.0f, float g = 1.0f, float b = 1.0f);

	std::string test = "";
};