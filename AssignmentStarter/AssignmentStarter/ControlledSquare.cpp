#include "pch.h"
#include "ControlledSquare.h"
#include <WICTextureLoader.h>

ControlledSquare::ControlledSquare(std::shared_ptr<DX::DeviceResources> resources)
{
	spriteTint = DirectX::SimpleMath::Color(DirectX::Colors::White.v);
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/Disc.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));

	// this gets the screen dimensions and sets the sprite possition
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	screenWidth = port.Width;
	screenHeight = port.Height;

	spritePosition.x = screenWidth / 2;
	spritePosition.y = screenHeight / 2;

	velocity = DirectX::SimpleMath::Vector2(200.0f, 200.0f);
}


ControlledSquare::~ControlledSquare()
{
}

void ControlledSquare::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		nullptr,
		this->spriteTint,
		0,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation and position.
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, 
		0.0f  
	);
	
	this->spriteBatch->End();
}

void ControlledSquare::Update(float timeDelta, std::shared_ptr<GameController> controller)
{
	DirectX::SimpleMath::Vector2 toMove = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	
	if (controller->IsButtonDown(XINPUT_GAMEPAD_X))
	{
		float vel = velocity.x * -1;

		float xDisplacement = vel * timeDelta;

		toMove.x = xDisplacement;
	}
	else if (controller->IsButtonDown(XINPUT_GAMEPAD_START))
	{
		float xDisplacement = velocity.x * timeDelta;

		toMove.x = xDisplacement;
	}
	else if (controller->IsButtonDown(XINPUT_GAMEPAD_Y))
	{
		float vel = velocity.y * -1;

		float yDisplacement = vel * timeDelta;

		toMove.y = yDisplacement;
	}
	else if (controller->IsButtonDown(XINPUT_GAMEPAD_A))
	{
		float yDisplacement = velocity.y * timeDelta;

		toMove.y = yDisplacement;
	}

	spritePosition += toMove;
}
