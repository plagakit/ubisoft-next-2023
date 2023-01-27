#include "stdafx.h"

#include <windows.h> 
#include <math.h>  

#include <App\app.h>


void Init() {}

void Update(float deltaTime)
{
	/*
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	*/
}


void Render()
{	
	App::Print(100, 100, "Sample Text");

	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}
}

void Shutdown()
{	
}