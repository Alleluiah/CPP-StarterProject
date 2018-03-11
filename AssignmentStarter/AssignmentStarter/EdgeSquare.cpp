#include "pch.h"
#include "EdgeSquare.h"
#include "WICTextureLoader.h"

// This selects the Disc image and loads it in
EdgeSquare::EdgeSquare(std::shared_ptr<DX::DeviceResources> resources)
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

	// This gets the current screen dimensions
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	screenWidth = port.Width;
	screenHeight = port.Height;

	// This selects the sprites position
	spritePosition.x = 0;
	spritePosition.y = 500;

	// This controls the sprites movement speed
	velocity = DirectX::SimpleMath::Vector2(32.0f, 64.0f);
}


EdgeSquare::~EdgeSquare()
{
}


void EdgeSquare::Render()
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
		DirectX::SimpleMath::Vector2(0, 0), 
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, 
		0.0f  
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}

void EdgeSquare::Update(float timeDelta)
{
	DirectX::SimpleMath::Vector2 displacement = velocity * timeDelta;

	spritePosition += displacement;

	if ((spritePosition.x > screenWidth - 400.0f) || (spritePosition.x < 0))
	{
		velocity.x *= -1;
	}

	if ((spritePosition.y > screenHeight - 600.0f) || (spritePosition.y < 0))
	{
		velocity.y *= -1;
	}
}
