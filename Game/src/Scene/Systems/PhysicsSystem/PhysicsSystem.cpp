#include <stdafx.h>

#include "Scene/Scene.h"
#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem(Scene* s) : scene(s) {}

void PhysicsSystem::UpdatePosition(Entity id)
{
	float dt = scene->m_deltaTime;
	
	Transform& tf = scene->GetComponent<Transform>(id);
	tf.position += tf.velocity * dt;
	tf.rotation += tf.velocity.y * dt * 0.1f;
	tf.velocity -= Vector2(0, 9.8 * dt);
}