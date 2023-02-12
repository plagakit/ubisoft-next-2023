#pragma once

#include <stdafx.h>

#include "EntityManager/EntityManager.h"
#include "ContiguousArray/ContiguousArray.h"

#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"
#include "Components/Timer/Timer.h"

#include "Systems/ISystem.h"
#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"
#include "Systems/TimerSystem/TimerSystem.h"


const Entity MAX_ENTITIES = 1000;

class Scene {

public:
	float m_deltaTime = 0;

	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();

	EntityManager& GetEntityManager();


private:
	EntityManager m_entityMgr;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;
	TimerSystem m_timerSystem;

};