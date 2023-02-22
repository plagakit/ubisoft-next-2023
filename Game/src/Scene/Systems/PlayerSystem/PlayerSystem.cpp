#include <stdafx.h>

#include "PlayerSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Transform/Transform.h"


void PlayerSystem::UpdatePlayer(Scene& scene)
{
	for (Entity id : scene.GetEntityManager().GetEntities<Wireframe, Transform>())
	{

		Transform& tf = scene.GetEntityManager().GetComponent <Transform>(id);
		
		if (App::IsKeyPressed('W'))
			tf.velocity += Vector2(0, 1).Rotated(tf.rotation);

		if (App::IsKeyPressed('A'))
			tf.rotation += 10 / 3.14f * scene.m_deltaTime;

		if (App::IsKeyPressed('D'))
			tf.rotation -= 10  / 3.14f * scene.m_deltaTime;

	}
}