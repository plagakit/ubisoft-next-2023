#include <stdafx.h>

#include "TimerSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Timer/Timer.h"


void TimerSystem::UpdateTimers(Scene& scene)
{
	for (Entity id : scene.GetEntities<Timer>())
	{
		Timer t = scene.GetComponent<Timer>(id);

		if (!t.isRunning)
			continue;

		t.elapsed += scene.m_smoothDeltaTime;

		if (t.elapsed > t.duration)
		{
			t.elapsed = 0.0f;
			if (t.oneFire)
			{
				t.done = true;
				t.isRunning = false;
			}

			s_TimerDone.Emit(scene, id);
		}

		scene.SetComponent<Timer>(id, t);
	}
	
}