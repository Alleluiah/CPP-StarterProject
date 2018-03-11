#include "pch.h"
#include "Glass.h"
#include <WICTextureLoader.h>

// This selects the cabinets png and loads it into the memory
Glass::Glass(std::shared_ptr<DX::DeviceResources> resources)
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

	// This selects the part of the cabinet.png that we want to load to the screen
	rect.top = 206.0f;
	rect.bottom = 276.0f;
	rect.right = 160.0f;
	rect.left = 128.0f;

	// This selects the position of the sprite on the screen
	spritePosition.x = 182.0f;
	spritePosition.y = 250.0f;
}

Glass::~Glass()
{

}


void Glass::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		&rect,
		this->spriteTint,
		0,  // This sets the angle of rotation on the sprite
		DirectX::SimpleMath::Vector2(0, 0), // This sets the origin of rotation on the sprite
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axis
		1.0f  // Sets the layer depth of the sprite
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}