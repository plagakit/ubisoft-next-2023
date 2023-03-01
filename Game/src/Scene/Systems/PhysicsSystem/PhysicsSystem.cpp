#include <stdafx.h>

#include "PhysicsSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"

void PhysicsSystem::UpdatePosition(Scene& scene)
{
	std::vector<Entity> bodies = scene.GetEntities<Transform, Physics>();
	for (Entity id : bodies)
	{
		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);

		// Update movement and rotation
		if (ph.bodyType == Physics::KINEMATIC)
		{
			tf.position += ph.velocity * scene.m_deltaTime;
			tf.rotation += ph.angularVelocity * scene.m_deltaTime;
		}
	}
}

// Detects collision between two entities and moves them according to their 
// Physics parameters. Both objects are modified, and the onCollision and
// onTrigger signal is emitted twice. Ensure that both entities has a Transform 
// & Physics component.
void PhysicsSystem::UpdateCollision(Scene& scene, Entity one, Entity two)
{
	bool collision = false;
	Transform& tf1 = scene.GetComponent<Transform>(one);
	Physics& ph1 = scene.GetComponent<Physics>(one);
	Transform& tf2 = scene.GetComponent<Transform>(two);
	Physics& ph2 = scene.GetComponent<Physics>(two);
	
	// Lots of ugly code and if statements (also bad because branch misprediction),
	// would get particularly ugly with 3+ types of bounds. An alternative would be 
	// to use inheritance to put all the specific bound x bound collision code 
	// inside subclasses so that C++ uses nice and fast vtable lookups instead of 
	// if statements. Did not implement because of time, but this solution still 
	// works nicely for my game due to its small size.

	// Circle x ?
	if (scene.HasComponent<CircleBounds>(one))
	{
		CircleBounds& cb1 = scene.GetComponent<CircleBounds>(one);

		// Circle x Circle
		if (scene.HasComponent<CircleBounds>(two))
		{
			CircleBounds& cb2 = scene.GetComponent<CircleBounds>(two);
			if (IsColliding(tf1, tf2, cb1, cb2))
			{
				collision = true;
			}
		}

		// Circle x Box
		if (scene.HasComponent<BoxBounds>(two))
		{
			BoxBounds& bb2 = scene.GetComponent<BoxBounds>(two);
			if (IsColliding(tf1, tf2, cb1, bb2))
			{
				collision = true;
			}
		}

	}

	// Box x ?
	if (scene.HasComponent<BoxBounds>(one))
	{
		BoxBounds& bb1 = scene.GetComponent<BoxBounds>(one);

		// Box x Circle
		if (scene.HasComponent<CircleBounds>(two))
		{
			CircleBounds& cb2 = scene.GetComponent<CircleBounds>(two);
			if (IsColliding(tf1, tf2, cb2, bb1))
			{
				collision = true;
			}
		}

		// Box x Box
		if (scene.HasComponent<BoxBounds>(two))
		{
			BoxBounds& bb2 = scene.GetComponent<BoxBounds>(two);
			if (IsColliding(tf1, tf2, bb1, bb2))
			{
				collision = true;
			}
		}
	}

	if (collision)
	{
		if (ph2.isTrigger) 
			s_onTrigger.Emit(one, two);
		else 
			s_onCollision.Emit(one, two);
	}
}

// Detects collision between two groups of entities and moves them according to their 
// Physics parameters. Modifies both entities, and so the onCollision/onTrigger signal 
// is emitted twice for each pair of entities. Ensure that every entity has a Transform 
// & Physics component.
void PhysicsSystem::UpdateCollision(Scene& scene, std::vector<Entity> group1, std::vector<Entity> group2)
{
	for (Entity i : group1)
		for (Entity j : group2)
			if (i != j)
				UpdateCollision(scene, i, j);
}


// Circle & circle
bool PhysicsSystem::IsColliding(Transform& tf1, Transform& tf2, CircleBounds& cb1, CircleBounds& cb2)
{
	float distSquared = (tf1.position + cb1.offset).DistanceSquared(tf2.position + cb2.offset);
	float collisionDistance = cb1.radius + cb2.radius;
	
	return distSquared < collisionDistance * collisionDistance;
}

// Box & box
bool PhysicsSystem::IsColliding(Transform& tf1, Transform& tf2, BoxBounds& bb1, BoxBounds& bb2)
{
	Vector2 p1 = tf1.position + bb1.offset;
	Vector2 p2 = tf2.position + bb2.offset;

	return p1.x + bb1.width / 2 > p2.x - bb2.width / 2 &&	// 1's right edge past 2's left
		p1.x - bb1.width / 2 < p2.x + bb2.width / 2	   &&   // 1's left edge past 2's right
		p1.y + bb1.height / 2 > p2.y - bb2.height / 2  &&   // 1's top edge past 2's bottom
		p1.y - bb1.height / 2 < p2.y + bb2.height / 2;      // 1's bottom edge past 2's top
}

// Circle & box
bool PhysicsSystem::IsColliding(Transform& tf1, Transform& tf2, CircleBounds& cb, BoxBounds& bb)
{
	Vector2 dist = (tf2.position + bb.offset) - (tf1.position + cb.offset);
	dist.x = abs(dist.x);
	dist.y = abs(dist.y);

	if (dist.x > (bb.width / 2 + cb.radius)) { return false; }	// If doesn't intersect sides
	if (dist.y > (bb.height / 2 + cb.radius)) { return false; } // If doesn't intersect top/bottom
	if (dist.x < (bb.width / 2)) { return true; } // If does intersect the sides
	if (dist.y < (bb.height / 2)) { return true; } // If does intersect the top/bottom

	float cornerDistSq = (dist.x - bb.width / 2) * (dist.x - bb.width / 2) +
		(dist.y - bb.height / 2) * (dist.y - bb.height / 2);

	return (cornerDistSq < cb.radius * cb.radius);
}