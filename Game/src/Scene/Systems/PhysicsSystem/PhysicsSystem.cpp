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

			// If object is moving & kinematic, check collision
			/*
			if (abs(ph.velocity.x) > 0 || abs(ph.velocity.y) > 0)
			{
				for (Entity other : scene.GetEntities<Transform, Physics>())
				{
					Transform& otf = scene.GetComponent<Transform>(other);
					Physics& oph = scene.GetComponent<Physics>(other);

					// Does not share any physics layer or is self
					if (other == id || (ph.layer | oph.layer) == 0)
						continue;

					if (scene.HasComponent<CircleBounds>(id))
						UpdateCircleCollision(scene, id, other);

					if (scene.HasComponent<BoxBounds>(id))
						UpdateBoxCollision(scene, id, other);

				}
			}
			*/
		}
	}
}

void PhysicsSystem::UpdateCircleCollision(Scene& scene, Entity id1, Entity id2)
{
	Transform& tf1 = scene.GetComponent<Transform>(id1);
	Physics& ph1 = scene.GetComponent<Physics>(id1);
	CircleBounds& cb = scene.GetComponent<CircleBounds>(id1);


	
}

void PhysicsSystem::UpdateBoxCollision(Scene& scene, Entity id1, Entity id2)
{
	Transform& tf1 = scene.GetComponent<Transform>(id1);
	Physics& ph1 = scene.GetComponent<Physics>(id1);
}

// Circle & circle
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb1, CircleBounds& cb2)
{
	return false;
}

// Box & box
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, BoxBounds& bb1, BoxBounds& bb2)
{
	return false;
}

// Circle & box
bool PhysicsSystem::IsColliding(Scene& scene, Entity id1, Entity id2, CircleBounds& cb, BoxBounds& bb)
{
	return false;
}