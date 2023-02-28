#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	for (Entity id : scene.GetEntities<Transform, Physics>())
	{
		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);

		// Update movement and rotation
		if (ph.bodyType == Physics::KINEMATIC)
		{
			tf.position += ph.velocity * scene.m_deltaTime;
			tf.rotation += ph.angularVelocity * scene.m_deltaTime;

			if (abs(ph.velocity.x) > 0 || abs(ph.velocity.y) > 0)
			{
				if (scene.HasComponent<CircleBounds>(id))
					UpdateCollision(scene, id, scene.GetComponent<CircleBounds>(id));

				if (scene.HasComponent<BoxBounds>(id))
					UpdateCollision(scene, id, scene.GetComponent<BoxBounds>(id));
			}
		}
	}
}

void PhysicsSystem::UpdateCollision(Scene& scene, Entity id, BoxBounds& bb)
{
	for (Entity other : scene.GetEntities<Transform, Physics>())
	{
		if (other == id) continue;



	}
}

void PhysicsSystem::UpdateCollision(Scene& scene, Entity id, CircleBounds& cb)
{
	for (Entity other : scene.GetEntities<Transform, Physics>())
	{
		if (other == id) continue;



	}
}

// Circle & circle
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb1, CircleBounds& cb2)
{

}

// Box & box
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, BoxBounds& bb1, BoxBounds& bb2)
{

}

// Circle & box
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb, BoxBounds& bb)
{

}