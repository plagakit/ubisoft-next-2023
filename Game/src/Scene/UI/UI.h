#pragma once

#include <stdafx.h>

#include "Core/Signal/Signal.h"
class Scene;
struct Camera;

class UI {

public:

	Signal<Camera> s_RenderWireframe;

	void Render(Scene& scene);

	void BindPlayer(Scene& scene, Entity player);
	void OnEntityDeleted(Scene& scene, Entity player);

private:
	Entity m_player;

};