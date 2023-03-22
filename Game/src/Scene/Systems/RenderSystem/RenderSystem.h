#pragma once

#include <stdafx.h>

class Scene;
class EntityManager;
struct Camera;
struct Vector2;
struct Transform;

class RenderSystem {

public:

	static const Vector2 CENTER;

	void Render(Scene& scene);

	void RenderSprite(Scene& scene, Entity id, Camera cam);
	void RenderWireframe(Scene& scene, Entity id, Camera cam);
	void RenderPhysicsBounds(Scene& scene);

	void DrawWireframe(const Camera camera, const Transform transform, const std::vector<Vector2>& points,
		float r = 1.0f, float g = 1.0f, float b = 1.0f);

};