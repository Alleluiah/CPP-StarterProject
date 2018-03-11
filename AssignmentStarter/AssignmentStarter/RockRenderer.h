#pragma once
#include "DeviceResources.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <CommonStates.h>
class RockRenderer
{
public:
	RockRenderer(std::shared_ptr<DX::DeviceResources> resources);
	~RockRenderer();

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	DirectX::SimpleMath::Vector2 spritePosition;
	DirectX::SimpleMath::Color spriteTint;
	std::unique_ptr<DirectX::CommonStates> commonStates;

public:
	void Render();

};

