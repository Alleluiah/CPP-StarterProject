#pragma once
#include "DeviceResources.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <CommonStates.h>
#include "GameController.h"
class ControlledSquare
{
public:
	ControlledSquare(std::shared_ptr<DX::DeviceResources> resources);
	~ControlledSquare();

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	DirectX::SimpleMath::Vector2 spritePosition;
	DirectX::SimpleMath::Color spriteTint;
	std::unique_ptr<DirectX::CommonStates> commonStates;

	DirectX::SimpleMath::Vector2 velocity;
	float screenWidth;
	float screenHeight;

public:
	void Render();
	void Update(float timeDelta, std::shared_ptr<GameController> controller);
};

