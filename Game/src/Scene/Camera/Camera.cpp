#include <stdafx.h>

#include "Camera.h"

#include "Scene/Scene.h"
#include "Utils/Utils.h"

Camera::Camera() :
	position(Vector2()), rotation(0), zoom(1.0f),
	offset(Vector2()), shakeTimer(Timer(0.25f)), shaking(false)
{
	shakeTimer.Start();
}

void Camera::Update(Scene& scene)
{
	if (shaking)
	{
		shakeTimer.elapsed += scene.m_deltaTime;

		if (shakeTimer.elapsed > shakeTimer.duration)
		{
			shaking = false;
			offset = Vector2(0, 0);
		}
		else
		{
			float fade = Utils::Lerp(1.0f, 0.5f, shakeTimer.PercentElapsed());
			float shake = sinf(shakeTimer.elapsed * fade * 50.0f) * 10.0f * fade;
			offset = Vector2(shake, 0);
		}
	}
}

void Camera::StartShake(Scene& scene, Entity _unused)
{
	shakeTimer.Start();
	shaking = true;
}