#pragma once

#include <stdafx.h>

//#include "Scene/Scene.h"
class Scene;

class RenderSystem {

public:
	RenderSystem(Scene* scene);
	void Render(Entity id);

private:
	Scene* scene;

};