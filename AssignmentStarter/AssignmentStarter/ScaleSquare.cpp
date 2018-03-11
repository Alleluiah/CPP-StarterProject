#include "pch.h"
#include "ScaleSquare.h"
#include <WICTextureLoader.h>
#include <CommonStates.h>

// Finds and loads the square sprite
ScaleSquare::ScaleSquare(std::shared_ptr<DX::DeviceResources> resources)
{
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(), 
			resources->GetD3DDeviceContext(), 
			L"Assets/Square.png", 
			0, 
			&this->texture
		));
	// this adds a tint of my choice to the image
	spriteTint = DirectX::Colors::Blue.v;

	D3D11_VIEWPORT viewPort = resources->GetScreenViewport();
	float right = viewPort.Width;
	float bottom = viewPort.Height;

	// Sets the postion of the sprite
	float xPos = 500;
	float yPos = 250;
	this->scale = 1.0f;

	xPos = xPos - 50;
	spritePosition = DirectX::SimpleMath::Vector2(xPos, yPos);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));

	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));
}

ScaleSquare::~ScaleSquare()
{
}

void ScaleSquare::Render()
{
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, this->commonStates->NonPremultiplied());

	this->spriteBatch->Draw(
		this->texture.Get(),
		this->spritePosition,
		nullptr,
		this->spriteTint,
		0.0f,
		DirectX::SimpleMath::Vector2(0, 0),
		scale,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f);

	this->spriteBatch->End();
}

void ScaleSquare::Update(std::shared_ptr<GameController> controller)
{
	// When the down DPAD is pressed it turns on both motors.
	if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		controller->SetVibration(30000, 30000);
	}
	// When the left DPAD button is pressed it sets the left motor to vibrate.
	if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		controller->SetVibration(30000, 0);
	}
	// When the right DPAD button is pressed it sets the right motor to vibrate.
	if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		controller->SetVibration(0, 30000);
	}
	// When the up DPAD is pressed it sets the vibration on both motors to 0.
	if (controller->WasButtonPressDetected(XINPUT_GAMEPAD_DPAD_UP))
	{
		controller->SetVibration(0, 0); 
	}

	this->scale = 1.0f + controller->getLeftNormalized();
}
