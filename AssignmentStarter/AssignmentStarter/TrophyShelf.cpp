#include "pch.h"
#include "TrophyShelf.h"
#include <WICTextureLoader.h>

// This loads the cabinets.png file into the memory
TrophyShelf::TrophyShelf(std::shared_ptr<DX::DeviceResources> resources)
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

	// This selects the part of the cabinets image and cuts it out
	rect.top = 0.0f;
	rect.bottom = 69.0f;
	rect.right = 128.0f;
	rect.left = 96.0f;

	// This selcts the postion of the sprite on the screen
	spritePosition.x = 182.0f;
	spritePosition.y = 250.0f;
}

TrophyShelf::~TrophyShelf()
{

}


void TrophyShelf::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(),  
		this->spritePosition,
		&rect,
		this->spriteTint,
		0,  // This is the angle of rotation of the sprite
		DirectX::SimpleMath::Vector2(0, 0), 
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, 
		0.0f  
	);
	//Instruct the SpriteBatch to actually render the sprites
	this->spriteBatch->End();
}
