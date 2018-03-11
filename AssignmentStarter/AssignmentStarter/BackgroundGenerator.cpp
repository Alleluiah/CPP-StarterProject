#include "pch.h"
#include "BackgroundGenerator.h"


BackgroundGenerator::BackgroundGenerator()
{
	red = 1.0f;
	blue = 1.0f;
	green = 1.0f;
}


BackgroundGenerator::~BackgroundGenerator()
{
}

DirectX::SimpleMath::Color BackgroundGenerator::Update(std::shared_ptr<GameController> controller)
{
	// When the B button is held down it gradually changes the background to red.
	if (controller->IsButtonDown(XINPUT_GAMEPAD_B))
	{
		red = red - 0.001f;
		green = green - 0.001f;
	}
	// When the right bumper is pressed reset the background colour
	if (controller->WasButtonPressDetected = false(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		red = 1.0f;
		blue = 1.0f;
		green = 1.0f;
	}


	// I kept on receiving errors when tring to do left bumper and the B button so I had to switch it to A.
	if (controller->IsButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER + XINPUT_GAMEPAD_A))
	{
		red = red - 0.001f;
	}

	return DirectX::SimpleMath::Color(red, green, blue, 1.0f);
}
