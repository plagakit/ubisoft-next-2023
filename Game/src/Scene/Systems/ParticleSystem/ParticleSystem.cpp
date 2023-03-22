#include <stdafx.h>

#include "ParticleSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/PrimitiveComponents.h"


void ParticleSystem::OnTimerDone(Scene& scene, Entity id)
{
	if (scene.HasComponent<Particle>(id))
		scene.QueueDelete(id);
}