#include "pch.h"
#include "CounterReverse.h"
#include <WICTextureLoader.h>
#include <CommonStates.h>
CounterReverse::CounterReverse(std::shared_ptr<DX::DeviceResources> resources) 
{
	spriteTint = DirectX::Colors::White.v;
	frameCount = 4;
	animationRate = 1.0/4.0;
	lastFrameChange = 0.0;
	tileWidth = 175.0f;
	currentFrame = 0;


	this->spriteBatch
		= std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(resources->GetD3DDeviceContext()));

	this->commonStates
		= std::unique_ptr<DirectX::CommonStates>(new DirectX::CommonStates(resources->GetD3DDevice()));

	// This loads the spriteanimation into the memory
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
		resources->GetD3DDevice(),
		resources->GetD3DDeviceContext(),
		L"Assets/SpriteAnimation.png",
		0,
		&this->texture
		)
		);

	PositionSprite(resources);

	// Sets the initial values
	rect.top = (long)0.0;
	rect.bottom = (long)202.0;
	rect.left = (long)0.0;
	rect.right = (long)175.0;
}


CounterReverse::~CounterReverse()
{
}

void CounterReverse::PositionSprite(std::shared_ptr<DX::DeviceResources> resources)
{
	D3D11_VIEWPORT viewPort = resources->GetScreenViewport();
	float right = viewPort.Width;
	float bottom = viewPort.Height;

	// Sets the position of the sprite onto the screen
	float xPos = 260;
	float yPos = 250;
	spritePosition = DirectX::SimpleMath::Vector2(xPos, yPos);
}

void CounterReverse::Render()
{
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, this->commonStates->NonPremultiplied());

	this->spriteBatch->Draw(
		this->texture.Get(),
		this->spritePosition,
		&rect,
		this->spriteTint,
		0.0f,
		DirectX::SimpleMath::Vector2(0, 0),
		0.5f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f);

	this->spriteBatch->End();
}

void CounterReverse::Update(double totalTime, double timeDelta)
{
	// this checks to see if the total time is gretaer than the previous update of the animation
	if (totalTime > lastFrameChange + animationRate)
	{
		// Updates the animation (sets it back to the start)
		if (currentFrame == frameCount)
		{
			currentFrame = 0;
		}

		
		// This finds the correct postion of the first image of the animation
		rect.top = (long)0;		
		rect.bottom = (long)202;
		rect.left = (long)(0 + (currentFrame * tileWidth));
		rect.right = (long)(rect.left + tileWidth);

		currentFrame++;
		lastFrameChange = totalTime;
	}
}