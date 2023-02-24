#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	for (Entity id : scene.GetEntityManager().GetEntities<Transform, Physics>())
	{
		Transform& tf = scene.GetEntityManager().GetComponent<Transform>(id);
		Physics& ph = scene.GetEntityManager().GetComponent<Physics>(id);
		
		// Update movement and rotation
		if (ph.bodyType == Physics::KINEMATIC)
		{
			tf.position += ph.velocity * scene.m_deltaTime;
			tf.rotation += ph.angularVelocity * scene.m_deltaTime;
		}

		// Only check collision for entities that moved
		if (abs(ph.velocity.x) > 0 || abs(ph.velocity.y) > 0)
		{

		}

	}
}

// Between 2 circles
bool PhysicsSystem::CheckCollision(Transform t1, Transform t2, CircleBounds c1, CircleBounds c2)
{
	float distance = (t1.position + c1.offset).Distance(t2.position + c2.offset);
	return distance < c1.radius + c2.radius;
}

// Between a circle and box
bool PhysicsSystem::CheckCollision(Transform t1, Transform t2, CircleBounds c, BoxBounds b)
{
	return false;
}

// Between 2 boxes
bool PhysicsSystem::CheckCollision(Transform t1, Transform t2, BoxBounds b1, BoxBounds b2)
{
	return false;
}