#include <stdafx.h>

#include "TimerSystem.h"
#include "Scene/Scene.h"
#include "Scene/Components/Timer/Timer.h"

void TimerSystem::Update(Entity id)
{
	Timer& t = scene->GetComponent<Timer>(id);
	
	if (!t.isRunning)
		return;

	t.elapsed += scene->m_deltaTime;

	if (t.elapsed > t.duration)
	{
		t.elapsed = 0.0f;
		t.done = true;
		if (t.oneFire)
		{
			t.isRunning = false;
			t.done = false;
		}	
	}
}