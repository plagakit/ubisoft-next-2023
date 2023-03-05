#include <stdafx.h>

#include "UI.h"

#include "Core/Signal/Signal.h"
#include "Scene/Scene.h"
#include "Scene/Components/Player/Player.h"
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/Physics/Physics.h"

void UI::Render(Scene& scene)
{
	if (scene.GetEntities<Player>().size() > 0)
	{
		const Health& playerHealth = scene.GetComponent<Health>(m_player);
		App::Print(20, 730, ("Health: " + std::to_string(playerHealth)).c_str());
		App::Print(20, 710, scene.GetComponent<Physics>(m_player).collisionNormal.ToString().c_str());
	}
}

void UI::BindPlayer(Scene& scene, Entity player)
{
	m_player = player;
}

