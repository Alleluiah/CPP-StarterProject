#include "pch.h"
#include "ElapsedTime.h"
#include <time.h>


// This selects the ElapsedTime.png and loads it into the memory
using namespace DirectX;
ElapsedTime::ElapsedTime(std::shared_ptr<DX::DeviceResources> resources)
	: m_fontPos(0, 0)
	, m_spriteBatch(nullptr)
{
	this->spriteFont
		= std::unique_ptr<SpriteFont>(new SpriteFont(resources->GetD3DDevice(), L"Assets/italic.spritefont"));

	this->m_spriteBatch =
		std::unique_ptr<SpriteBatch>(new SpriteBatch(resources->GetD3DDeviceContext()));

	// This selects the postion of the sprite on the screen and selects the tint colour of the text
	origin = DirectX::SimpleMath::Vector2(-500, -100);
	tint = DirectX::Colors::Black.v;
}

ElapsedTime::~ElapsedTime()
{

}


void ElapsedTime::Render()
{
	m_spriteBatch->Begin();
	// This is where I selected the text i wanted printing to the screen
	const wchar_t* output = L"Elapsed time = ";

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
