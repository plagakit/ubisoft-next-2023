#include <stdafx.h>

#include "UI.h"

#include "Core/Signal/Signal.h"
#include "Scene/Scene.h"
#include "Scene/Components/Player/Player.h"
#include "Scene/Components/Zombie/Zombie.h"
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/Physics/Physics.h"

void UI::Render(Scene& scene)
{
	if (m_player != Scene::NULL_ENTITY)
	{
		const Health playerHealth = scene.GetComponent<Health>(m_player);
		App::Print(20, 725, ("Health: " + std::to_string(playerHealth)).c_str());
	}

	const auto points = "Points: " + std::to_string(scene.m_points);
	App::Print(20, 700, points.c_str());

	const auto wave = "Wave #" + std::to_string(scene.m_waveNum);
	App::Print(20, 675, wave.c_str());

	const auto zombCount = scene.GetEntities<Zombie>().size();
	const auto zomb = "Zombies Left: " + std::to_string(zombCount);
	App::Print(20, 650, zomb.c_str());

#ifdef _DEBUG
	App::Print(20, 600, std::to_string(scene.m_smoothDeltaTime).c_str());
	App::Print(20, 575, std::to_string(scene.GetCount()).c_str());
#endif
}

void UI::BindPlayer(Scene& scene, Entity player)
{
	m_player = player;
}

void UI::OnEntityDeleted(Scene& scene, Entity id)
{
	if (id == m_player)
		m_player = Scene::NULL_ENTITY;
}
