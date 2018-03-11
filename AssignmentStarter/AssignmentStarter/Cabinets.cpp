#include "pch.h"
#include "Cabinets.h"
#include <WICTextureLoader.h>


Cabinets::Cabinets(std::shared_ptr<DX::DeviceResources> resources)
{
	//this tints the sprite and selects it
	spriteTint = DirectX::Colors::White.v;
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			resources->GetD3DDevice(),
			resources->GetD3DDeviceContext(),
			L"Assets/Cabinets.png",
			0,
			&this->texture
		)
	);

	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));
	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));
	// This cuts out the part of the spritesheet that i wanted
	rect.top = 0.0f;
	rect.bottom = 69.0f;
	rect.right = 128.0f;
	rect.left = 0.0f;

	// This inputs the position i want the sprite to load
	spritePosition.x = 100.0f;
	spritePosition.y = 10.0f;
}

Cabinets::~Cabinets()
{

}


void Cabinets::Render()
{
	spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		this->commonStates->NonPremultiplied());

	
	this->spriteBatch->Draw(
		this->texture.Get(), 
		this->spritePosition,
		&rect,
		this->spriteTint,
		0,  // This is the angle of rotation on the sprite
		DirectX::SimpleMath::Vector2(0, 0), //Origin of rotation on the sprite
		1.0f, //Scale factor
		DirectX::SpriteEffects::SpriteEffects_None, //Reflections about the horizontal and verticle axis
		0.0f  
	);
	
	this->spriteBatch->End();
}