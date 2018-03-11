#pragma once
#include "DeviceResources.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <CommonStates.h>
class Counter
{
public:
	Counter(std::shared_ptr<DX::DeviceResources> resources);
	~Counter();

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;

	DirectX::SimpleMath::Vector2 spritePosition;

	DirectX::SimpleMath::Color spriteTint;

	std::unique_ptr<DirectX::CommonStates> commonStates;

private:
	// for anumation
	double animationRate;
	double lastFrameChange;
	int frameCount;
	int currentFrame;
	RECT rect;
	float tileWidth;


public:
	void Render();
	void Update(double totalTime, double timeDelta);

private:
	void PositionSprite(std::shared_ptr<DX::DeviceResources> resources);
};

