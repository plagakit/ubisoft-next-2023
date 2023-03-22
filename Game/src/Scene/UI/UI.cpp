#include <stdafx.h>

#include "UI.h"

#include "Core/Signal/Signal.h"
#include "Utils/Utils.h"
#include "Scene/Scene.h"
#include "Scene/Camera/Camera.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Player/Player.h"
#include "Scene/Components/Zombie/Zombie.h"
#include "Scene/Components/PrimitiveComponents.h"
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/Physics/Physics.h"


void UI::Render(Scene& scene) const
{
	if (m_player != Scene::NULL_ENTITY)
	{
		const Health playerHealth = scene.GetComponent<Health>(m_player);
		App::Print(20, 725, ("Health: " + std::to_string(playerHealth)).c_str());
	}

	App::Print(20, 20, "Arrows keys to move.");
	App::Print(20, 40, "Press X to kick a bomb.");
	App::Print(20, 60, "Press Z to place a bomb.");

	const auto points = "Points: " + std::to_string(scene.m_points);
	App::Print(20, 700, points.c_str());

	const auto wave = "Wave #" + std::to_string(scene.m_waveNum);
	App::Print(20, 675, wave.c_str());

	const auto zombCount = scene.GetEntities<Zombie>().size();
	const auto zomb = "Zombies Left: " + std::to_string(zombCount);
	App::Print(20, 650, zomb.c_str());

	const auto combo = "Combo: " + std::to_string(scene.m_combo);
	App::Print(20, 625, combo.c_str());


	if (scene.m_combo > 0)
	{
		Entity comboTimer = scene.m_comboTimer;
		const Timer tm = scene.GetComponent<Timer>(comboTimer);

		float progression = tm.PercentElapsed();
		float w = Utils::Lerp(60.0f, 0.0f, progression);
		float h = 15.0f;

		Vector2 offset = Vector2(20, 600);
		Color color = Utils::Lerp(Color(Colors::RED), Color(Colors::BLUE), progression);

		float r = color.r / 255.0f;
		float g = color.g / 255.0f;
		float b = color.b / 255.0f;
		App::DrawLine(offset.x, offset.y, offset.x + w, offset.y, r, g, b);
		App::DrawLine(offset.x, offset.y + h, offset.x + w, offset.y + h, r, g, b);
		App::DrawLine(offset.x, offset.y, offset.x, offset.y + h, r, g, b);
		App::DrawLine(offset.x + w, offset.y, offset.x + w, offset.y + h, r, g, b);
	}

#ifdef _DEBUG
	App::Print(20, 500, std::to_string(scene.m_smoothDeltaTime).c_str());
	App::Print(20, 475, std::to_string(scene.GetCount()).c_str());
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
