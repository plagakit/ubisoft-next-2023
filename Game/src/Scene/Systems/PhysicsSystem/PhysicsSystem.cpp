#include <stdafx.h>

#include "Scene/Scene.h"
#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem(Scene* s) : scene(s) {}

void PhysicsSystem::UpdatePosition(Entity id)
{
	float dt = scene->m_deltaTime;
	
	Transform& tf = scene->GetTransform(id);
	tf.position += tf.velocity * dt;
	tf.velocity -= Vector2(0, 9.8 * dt);
}