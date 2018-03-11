#include "pch.h"
#include "Square.h"
#include "WICTextureLoader.h"

// This selects the square. png and loads it into the memory
Square::Square(std::shared_ptr<DX::DeviceResources> resources)
{
	spriteTint = DirectX::SimpleMath::Color(DirectX::Colors::White.v);
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/Square.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));

	// This gets the current screen dimensions
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	screenWidth = port.Width;
	screenHeight = port.Height;

	// This selects the postion of the sprite
	spritePosition.x = 10;
	spritePosition.y = 100;

	// This controls the speed of the sprite as it moves across the screen
	velocity = DirectX::SimpleMath::Vector2(32.0f, 0.0f);
}


Square::~Square()
{
}


void Square::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		nullptr,
		this->spriteTint,
		0,  // This sets the angle of rotation on the sprite
		DirectX::SimpleMath::Vector2(0, 0), // This sets the origin of rotation of the sprite
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axis
		0.0f  // This selcts the layer depth of the sprite
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}

void Square::Update(float timeDelta)
{
	DirectX::SimpleMath::Vector2 displacement = velocity * timeDelta;

	spritePosition += displacement;

	if ((spritePosition.x > screenWidth - 32.0f) || (spritePosition.x < 0))
	{
		velocity.x *= -1;
	}

	if ((spritePosition.y > screenHeight - 32.0f) || (spritePosition.y < 0))
	{
		velocity.y *= -1;
	}
}
