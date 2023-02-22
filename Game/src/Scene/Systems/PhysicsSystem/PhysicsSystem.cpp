#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	for (Entity id : scene.GetEntityManager().GetEntities<Transform>())
	{
		Transform& tf = scene.GetEntityManager().GetComponent<Transform>(id);
		tf.position += tf.velocity * scene.m_deltaTime;
	}
}