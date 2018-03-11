#include "pch.h"
#include "Trophy.h"
#include <WICTextureLoader.h>

// This loads the cabinets image
Trophy::Trophy(std::shared_ptr<DX::DeviceResources> resources)
{
	spriteTint = DirectX::Colors::White.v;
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/cabinets.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));
	// This cuts out the part of the sprite sheet that i want
	rect.top = 0.0f;
	rect.bottom = 69.0f;
	rect.right = 64.0f;
	rect.left = 32.0f;

	// This selcts the postion of the sprite 
	spritePosition.x = 150.0f;
	spritePosition.y = 250.0f;
}

Trophy::~Trophy()
{

}


void Trophy::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		&rect,
		this->spriteTint,
		0,  // This selcts the angle of rotation
		DirectX::SimpleMath::Vector2(0, 0), 
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, 
		0.0f  
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}