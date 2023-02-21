#pragma once

#include <stdafx.h>

#include "EntityManager/EntityManager.h"
#include "ContiguousArray/ContiguousArray.h"

#include "Components/Transform/Transform.h"
#include "Components/Sprite/Sprite.h"
#include "Components/Timer/Timer.h"
#include "Components/Wireframe/Wireframe.h"

#include "Systems/RenderSystem/RenderSystem.h"
#include "Systems/PhysicsSystem/PhysicsSystem.h"
#include "Systems/TimerSystem/TimerSystem.h"

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

	Camera m_camera;

};