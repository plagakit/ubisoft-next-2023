#include <stdafx.h>

#include "Scene/Scene.h"
#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem(Scene* s) : scene(s) {}

void PhysicsSystem::UpdatePosition(Entity id, float deltaTime)
{
	Transform& tf = scene->GetTransform(id);
	tf.position += tf.velocity * deltaTime / 60;
	tf.velocity -= Vector2(0, 0.98f * deltaTime / 60);
}