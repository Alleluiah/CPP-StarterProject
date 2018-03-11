#pragma once
#include "SpriteBatch.h"
#include "CommonStates.h"
#include "SimpleMath.h"
#include "DeviceResources.h"

class TrophyShelf
{
public:
	TrophyShelf(std::shared_ptr<DX::DeviceResources> resources);
	~TrophyShelf();

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	DirectX::SimpleMath::Vector2 spritePosition;
	DirectX::SimpleMath::Color spriteTint;
	std::unique_ptr<DirectX::CommonStates> commonStates;

	RECT rect;

public:
	void Render();
};
