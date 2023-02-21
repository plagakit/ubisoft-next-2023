#include <stdafx.h>

#include "TimerSystem.h"
#include "Scene/Scene.h"


void TimerSystem::UpdateTimers(Scene& scene)
{
	for (Entity id : scene.GetEntityManager().GetEntities<Timer>())
	{
		Timer& t = scene.GetEntityManager().GetComponent<Timer>(id);

		if (!t.isRunning)
			return;

		t.elapsed += scene.m_deltaTime;

		if (t.elapsed > t.duration)
		{
			t.elapsed = 0.0f;
			if (t.oneFire)
			{
				t.done = true;
				t.isRunning = false;
			}
			e_timerFired.Emit();
		}
	}
	
}