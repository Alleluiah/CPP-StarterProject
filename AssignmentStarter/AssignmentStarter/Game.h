

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "RockRenderer.h"
#include "Cabinets.h"
#include "Square.h"
#include "BarrelRenderer.h"
#include "RotatedBarrel.h"
#include "Trophy.h"
#include "TrophyShelf.h"
#include "Glass.h"
#include "GameController.h"
#include "ScaleSquare.h"
#include "TextDraw.h"
#include "BackgroundGenerator.h"
#include "Counter.h"
#include "CounterReverse.h"
#include "ControlledSquare.h"
#include "ElapsedTime.h"
#include "EdgeSquare.h"
//#include "Vibration.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
	
	
	DirectX::SimpleMath::Color m_backgroundColor;

    // Device resources.
    std::shared_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
	std::shared_ptr<RockRenderer> m_RockRenderer;
	std::shared_ptr<Cabinets> m_Cabinets;
	std::shared_ptr<Square> m_Square;
	std::shared_ptr<BarrelRenderer> m_BarrelRenderer;
	std::shared_ptr<RotatedBarrel> m_RotatedBarrel;
	std::shared_ptr<Trophy> m_Trophy;
	std::shared_ptr<TrophyShelf> m_TrophyShelf;
	std::shared_ptr<Glass> m_Glass;
	std::shared_ptr<GameController> m_gamepad;
	std::shared_ptr<ScaleSquare> m_ScaleSquare;
	std::shared_ptr<TextDraw> m_textDraw;
	std::shared_ptr<BackgroundGenerator> m_backgroundGenerator;
	std::shared_ptr<Counter> m_Counter;
	std::shared_ptr<CounterReverse> m_CounterReverse;
	std::shared_ptr<ControlledSquare> m_ControlledSquare;
	std::shared_ptr<ElapsedTime> m_ElapsedTime;
	std::shared_ptr<EdgeSquare> m_EdgeSquare;

};