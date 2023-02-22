#pragma once

#include <stdafx.h>

#include "EntityManager/EntityManager.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"
#include "Systems/TimerSystem/TimerSystem.h"
#include "Systems/PlayerSystem/PlayerSystem.h"

#include "Camera/Camera.h"


const Entity MAX_ENTITIES = 1000;

class Scene {

public:
	float m_deltaTime = 0;

	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();

	EntityManager& GetEntityManager();
	Camera& GetCamera();


private:
	EntityManager m_entityMgr;

	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;
	TimerSystem m_timerSystem;
	PlayerSystem m_playerSystem;

	Camera m_camera;

};