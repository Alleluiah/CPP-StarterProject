#pragma once
#include "SpriteFont.h"
#include "SimpleMath.h"
#include "DeviceResources.h"
#include "SpriteBatch.h"
class TextDraw
{
public:
	TextDraw(std::shared_ptr<DX::DeviceResources> resources);
	~TextDraw();

private:
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
	DirectX::SimpleMath::Vector2 m_fontPos;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	DirectX::SimpleMath::Vector2 origin;
	DirectX::SimpleMath::Color tint;

public:
	void Render();
};

