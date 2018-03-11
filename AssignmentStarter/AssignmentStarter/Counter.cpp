#include "pch.h"
#include "Counter.h"
#include <WICTextureLoader.h>
#include <CommonStates.h>
// Sets the basic parts of the animation
Counter::Counter(std::shared_ptr<DX::DeviceResources> resources) 
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

	// This finds the sprite that will be animated
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

	// This sets the size of the frames that will be cut from the spritesheet
	rect.top = (long)0.0;
	rect.bottom = (long)202.0;
	rect.left = (long)0.0;
	rect.right = (long)175.0;
}


Counter::~Counter()
{
}

void Counter::PositionSprite(std::shared_ptr<DX::DeviceResources> resources)
{
	D3D11_VIEWPORT viewPort = resources->GetScreenViewport();
	float right = viewPort.Width;
	float bottom = viewPort.Height;

	// This sets the position of the sprites on the screen
	float xPos = 260;
	float yPos = 10;
	spritePosition = DirectX::SimpleMath::Vector2(xPos, yPos);
}

void Counter::Render()
{
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, this->commonStates->NonPremultiplied());

	this->spriteBatch->Draw(
		this->texture.Get(),
		this->spritePosition,
		&rect,
		this->spriteTint,
		0.0f,
		DirectX::SimpleMath::Vector2(0, 0),
		1.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f);

	this->spriteBatch->End();
}

void Counter::Update(double totalTime, double timeDelta)
{
	// This checks to see if the total time is greater than the last update of the aniamtion
	if (totalTime > lastFrameChange + animationRate)
	{
		// If the current frame is at the end rest the frame to the first image of the animation
		if (currentFrame == frameCount)
		{
			currentFrame = 0;
		}

		// Selects the postion of the first picture in the animation
		rect.top = (long)0;		
		rect.bottom = (long)202;
		rect.left = (long)(0 + (currentFrame * tileWidth));
		rect.right = (long)(rect.left + tileWidth);

		currentFrame++;
		lastFrameChange = totalTime;
	}
}