#include "pch.h"
#include "RotatedBarrel.h"
#include <WICTextureLoader.h>
#include "CommonStates.h"

// Finds the Barrel png and selects it
RotatedBarrel::RotatedBarrel(std::shared_ptr<DX::DeviceResources> resources)
{
	spriteTint = DirectX::SimpleMath::Color(DirectX::Colors::White.v);
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/barrel.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));

	// Gets the screnns dimensions
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	float screenWidth = port.Width;
	float screenHeight = port.Height;

	// This positions the sprites on the screen.
	spritePosition.x = 10;
	spritePosition.y = 250;
}

RotatedBarrel::~RotatedBarrel()
{

}


void RotatedBarrel::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	//Give the SpriteBatch a single sprite
	this->spriteBatch->Draw(
		this->texture.Get(), 
		this->spritePosition,
		nullptr,
		this->spriteTint,
		3.14159,  // Selects the angle of rotation on the sprite
		DirectX::SimpleMath::Vector2(128, 32), // Finds the origin of rotation on the sprite
		1.0f, // This is the scale factor of the sprite
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axis
		0.0f  // This is the layer depth of the sprite
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();

}