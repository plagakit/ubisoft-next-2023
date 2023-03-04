#pragma once

#include <stdafx.h>

class Scene;

class UI {

public:
	void Render(Scene& scene);

	void BindPlayer(Scene& scene, Entity player);

private:
	Entity m_player;

};