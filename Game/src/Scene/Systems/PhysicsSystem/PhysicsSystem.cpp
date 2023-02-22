#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	for (Entity id : scene.GetEntityManager().GetEntities<Transform>())
	{
		Transform& tf = scene.GetEntityManager().GetComponent<Transform>(id);
		Physics& ph = scene.GetEntityManager().GetComponent<Physics>(id);
		
		if (ph.bodyType == Physics::KINEMATIC)
		{
			tf.position += ph.velocity * scene.m_deltaTime;
			tf.rotation += ph.angularVelocity * scene.m_deltaTime;
		}

	}
}