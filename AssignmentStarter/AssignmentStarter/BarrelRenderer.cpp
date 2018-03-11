#include "pch.h"
#include "BarrelRenderer.h"
#include <WICTextureLoader.h>
#include "CommonStates.h"

// Finds the correct image and selects it
BarrelRenderer::BarrelRenderer(std::shared_ptr<DX::DeviceResources> resources)
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

	// This finds the dimensions of the screen
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	float screenWidth = port.Width;
	float screenHeight = port.Height;

	// These are the positions the sprite will be loaded in.
	spritePosition.x = port.Width - 128;
	spritePosition.y = port.Height - 64;
}

BarrelRenderer::~BarrelRenderer()
{

}


void BarrelRenderer::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(), 
		this->spritePosition,
		nullptr,
		this->spriteTint,
		0,  // This selects the angle of rotation for the sprite.
		DirectX::SimpleMath::Vector2(0, 0), 
		1.0f, // This is the scale factor of the sprite
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();

}