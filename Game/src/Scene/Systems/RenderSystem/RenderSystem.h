#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

class RenderSystem : public ISystem {
	using ISystem::ISystem;

private:
	void Render(EntityManager& entityMgr, Entity id);
	void RenderWireframe(EntityManager& entityMgr, Entity id);

public:
	void Update(EntityManager& entityMgr);

};