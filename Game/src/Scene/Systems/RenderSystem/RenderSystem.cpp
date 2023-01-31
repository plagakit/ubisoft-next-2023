#include <stdafx.h>

#include "RenderSystem.h"
#include "Scene/Scene.h"

RenderSystem::RenderSystem(Scene* s) : scene(s) {}

void RenderSystem::Render(Entity id) 
{	
	Transform tf = scene->GetTransform(id);
	Sprite sp = scene->GetSprite(id);

	float sx = tf.position.x - sp.width / 2.0f;
	float sy = tf.position.y - sp.height / 2.0f;
	int r = sp.r, g = sp.g, b = sp.b;

	App::DrawLine(sx, sy, sx + sp.width, sy, r, g, b);
	App::DrawLine(sx, sy, sx, sy + sp.height, r, g, b);
	App::DrawLine(sx, sy + sp.height, sx + sp.width, sy + sp.height, r, g, b);
	App::DrawLine(sx + sp.width, sy, sx + sp.width, sy + sp.height, r, g, b);
}