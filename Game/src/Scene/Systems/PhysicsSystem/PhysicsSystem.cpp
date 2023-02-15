#include <stdafx.h>

#include "PhysicsSystem.h"
#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"


void PhysicsSystem::UpdatePosition(Entity id)
{
	float dt = scene->m_deltaTime;
	
	Transform& tf = scene->GetEntityManager().GetComponent<Transform>(id);
	tf.position += tf.velocity * dt;
	tf.rotation += dt * 0.1f;
}