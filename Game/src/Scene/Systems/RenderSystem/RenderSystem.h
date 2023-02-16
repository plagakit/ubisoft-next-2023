#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISignalManager/ISignalManager.h"

struct Camera;
class EntityManager;

class RenderSystem : public ISignalManager {

public:
	void Render(Scene& scene);

private:
	void RenderSprite(Camera& camera, EntityManager& entityMgr, Entity id);
	void RenderWireframe(Camera& camera, EntityManager& entityMgr, Entity id);

};