#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	auto mgr = scene.GetEntityManager();
	for (Entity id : scene.GetEntityManager().GetEntities<Transform, Physics>())
	{
		Transform& tf = mgr.GetComponent<Transform>(id);
		Physics& ph = mgr.GetComponent<Physics>(id);

		// Update movement and rotation
		if (ph.bodyType == Physics::KINEMATIC)
		{
			tf.position += ph.velocity * scene.m_deltaTime;
			tf.rotation += ph.angularVelocity * scene.m_deltaTime;
		}
	}
}