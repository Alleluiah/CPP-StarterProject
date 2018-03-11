#pragma once
#include "DeviceResources.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <CommonStates.h>
#include "GameController.h"
class ScaleSquare
{
public:
	ScaleSquare(std::shared_ptr<DX::DeviceResources> resources);
	~ScaleSquare();

private:

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;

	DirectX::SimpleMath::Vector2 spritePosition;

	DirectX::SimpleMath::Color spriteTint;

	std::unique_ptr<DirectX::CommonStates> commonStates;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	float scale;

public:
	void Render();
	void Update(std::shared_ptr<GameController> controller);
};

