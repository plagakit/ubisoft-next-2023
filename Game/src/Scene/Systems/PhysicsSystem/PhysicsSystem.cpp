#include <stdafx.h>

#include "PhysicsSystem.h"
#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"


void PhysicsSystem::UpdatePosition(Entity id)
{
	float dt = scene->m_deltaTime;
	
	Transform& tf = scene->GetComponentManager().GetComponent<Transform>(id);
	tf.position += tf.velocity * dt;
	tf.rotation += tf.velocity.y * dt * 0.1f;
	tf.velocity -= Vector2(0, 9.8 * dt);
}