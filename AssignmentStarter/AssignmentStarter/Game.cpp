

#include "pch.h"
#include "Game.h"

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game()
{
    m_deviceResources = std::make_shared<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    
	m_RockRenderer = std::make_shared <RockRenderer>(m_deviceResources);
	m_Cabinets = std::make_shared <Cabinets>(m_deviceResources);
	m_Square = std::make_shared <Square>(m_deviceResources);
	m_BarrelRenderer = std::make_shared <BarrelRenderer>(m_deviceResources);
	m_RotatedBarrel = std::make_shared <RotatedBarrel>(m_deviceResources);
	m_Trophy = std::make_shared <Trophy>(m_deviceResources);
	m_TrophyShelf = std::make_shared <TrophyShelf>(m_deviceResources);
	m_Glass = std::make_shared <Glass>(m_deviceResources);
	m_backgroundGenerator = std::make_shared<BackgroundGenerator>();
	m_textDraw = std::make_shared<TextDraw>(m_deviceResources);
	m_gamepad = std::make_shared<GameController>();
	m_ScaleSquare = std::make_shared<ScaleSquare>(m_deviceResources);
	m_Counter = std::make_shared<Counter>(m_deviceResources);
	m_CounterReverse = std::make_shared<CounterReverse>(m_deviceResources);
	m_ControlledSquare = std::make_shared<ControlledSquare>(m_deviceResources);
	m_ElapsedTime = std::make_shared<ElapsedTime>(m_deviceResources);
	m_EdgeSquare = std::make_shared <EdgeSquare>(m_deviceResources);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
	float totalSeconds = float(timer.GetTotalSeconds());

   //these will update as the game world updates
	
	m_Square->Update(elapsedTime);
	m_Counter->Update(totalSeconds, elapsedTime);
	m_CounterReverse->Update(totalSeconds, elapsedTime);
	m_EdgeSquare->Update(elapsedTime);
	m_ScaleSquare->Update(m_gamepad);
	m_gamepad->Update();
	m_backgroundColor = m_backgroundGenerator->Update(m_gamepad);
	elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

	// Renders each image onto the screen
	
	m_RotatedBarrel->Render();
	m_RockRenderer->Render();
	m_Cabinets->Render();
	m_BarrelRenderer->Render();
	m_CounterReverse->Render();
	m_Trophy->Render();
	m_TrophyShelf->Render();
	m_Glass->Render();
	m_ScaleSquare->Render();
	m_textDraw->Render();
	m_Counter->Render();
	m_ElapsedTime->Render();
	m_Square->Render();
	m_ControlledSquare->Render();
	m_EdgeSquare->Render();

	// Renders the background, takes values for the vibration class
	

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, m_backgroundColor);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    
}

void Game::OnDeactivated()
{
    
}

void Game::OnSuspending()
{
    
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
  
}

void Game::OnDeviceLost()
{
 
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

#pragma endregion
