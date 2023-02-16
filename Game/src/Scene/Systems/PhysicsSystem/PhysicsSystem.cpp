#include <stdafx.h>

#include "PhysicsSystem.h"
#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"

void PhysicsSystem::Update(Scene& scene)
{
	float dt = scene.m_deltaTime;
	EntityManager& entityMgr = scene.GetEntityManager();
	
	// Update position
	for (Entity id : entityMgr.GetEntities<Transform>())
	{
		Transform& tf = entityMgr.GetComponent<Transform>(id);
		tf.position += tf.velocity * dt;
	}

}