#include "pch.h"
#include "TextDraw.h"

// This selects the font that i want to use
using namespace DirectX;
TextDraw::TextDraw(std::shared_ptr<DX::DeviceResources> resources)
	: m_fontPos(0, 0)
	, m_spriteBatch(nullptr)
{
	this->spriteFont
		= std::unique_ptr<SpriteFont>(new SpriteFont(resources->GetD3DDevice(), L"Assets/italic.spritefont"));

	this->m_spriteBatch =
		std::unique_ptr<SpriteBatch>(new SpriteBatch(resources->GetD3DDeviceContext()));
	
	// This selects the postion of the sprite and its selected colour tint
	origin = DirectX::SimpleMath::Vector2(-500, -10);
	tint = DirectX::Colors::Yellow.v;
}

TextDraw::~TextDraw()
{

}


void TextDraw::Render()
{
	m_spriteBatch->Begin();
	// This is where I entered the text i wanted printing onto the screen
	const wchar_t* output = L"Hello Game World";
	
	spriteFont->DrawString(
		m_spriteBatch.get(), 
		output,
		m_fontPos, 
		tint, 
		0.f, 
		origin
		);
	m_spriteBatch->End();
}