#include "pch.h"
#include "ROCKRENDERER.H"
#include <WICTextureLoader.h>

// This selects the rock image and loads it
RockRenderer::RockRenderer(std::shared_ptr<DX::DeviceResources> resources)
{
	spriteTint = DirectX::SimpleMath::Color(DirectX::Colors::Green.v);
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/rock.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));

	// This gets the screen dimensions
	D3D11_VIEWPORT port = resources->GetScreenViewport();
	float screenWidth = port.Width;
	float screenHeight = port.Height;

	// This sets the postion of the sprite
	spritePosition.x = 10.0f;
	spritePosition.y = 10.0f;
}


RockRenderer::~RockRenderer()
{
}

void RockRenderer::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		nullptr,
		this->spriteTint,
		0,  // This sets the angle of rotation of the sprite
		DirectX::SimpleMath::Vector2(0, 0), 
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, 
		0.0f  
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}