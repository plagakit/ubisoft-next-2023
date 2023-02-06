#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISystem.h"

class RenderSystem : public ISystem {
	using ISystem::ISystem;

public:
	void Render(Entity id);

};