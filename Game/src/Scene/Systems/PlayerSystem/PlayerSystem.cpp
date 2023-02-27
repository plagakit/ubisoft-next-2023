#include <stdafx.h>

#include "PlayerSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Physics/Physics.h"


void PlayerSystem::UpdatePlayer(Scene& scene)
{
	for (Entity id : scene.GetEntities<Wireframe, Transform, Physics>())
	{

		Transform& tf = scene.GetComponent<Transform>(id);
		Physics& ph = scene.GetComponent<Physics>(id);
		
		if (App::IsKeyPressed('W'))
			ph.velocity += Vector2(0, 1).Rotated(tf.rotation);

		if (App::IsKeyPressed('A'))
			ph.angularVelocity += 0.25f / 3.14f;

		if (App::IsKeyPressed('D'))
			ph.angularVelocity -= 0.25f / 3.14f;

		if (ph.angularVelocity > 1.57f)
			ph.angularVelocity = 1.57f;
		else if (ph.angularVelocity < -1.57f)
			ph.angularVelocity = -1.57f;
		
		//ph.angularVelocity -= (ph.angularVelocity > 0) - (ph.angularVelocity < 0);aa

	}
}