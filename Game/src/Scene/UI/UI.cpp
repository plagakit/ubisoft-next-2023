#include <stdafx.h>

#include "UI.h"

#include "Scene/Scene.h"
#include "Scene/Components/PrimitiveComponents.h"

void UI::Render(Scene& scene)
{
	const Health& playerHealth = scene.GetComponent<Health>(m_player);
	App::Print(20, 730, ("Health: " + std::to_string(playerHealth)).c_str());
}

void UI::BindPlayer(Scene& scene, Entity player)
{
	m_player = player;
}