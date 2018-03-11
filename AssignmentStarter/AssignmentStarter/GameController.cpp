#include "pch.h"
#include "GameController.h"
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::Update()
{
	//Store the previous state of the gamepad
	this->gamepadStatePrevious = this->gamepadState;

	
	ZeroMemory(&this->gamepadState, sizeof(XINPUT_STATE));

	DWORD dwResult = XInputGetState(0, &this->gamepadState);
	if (dwResult == ERROR_SUCCESS)
	{
		this->gamepadConnected = true;
		this->UpdateAnalog();
		this->UpdateRightTriggerNormalised();
	}
	else
	{
		this->gamepadConnected = false;
	}

}

void GameController::UpdateAnalog()
{
	float LX = gamepadState.Gamepad.sThumbLX;
	float LY = gamepadState.Gamepad.sThumbLY;

	
	float magnitude = sqrt(LX*LX + LY*LY);

	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	normalizedMagnitude = 0;

	//check if the controller is outside of the set deadzone
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		if (magnitude > 32767)
		{
			magnitude = 32767;
		}

		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
}

void GameController::UpdateRightTriggerNormalised()
{
	float value = gamepadState.Gamepad.bRightTrigger;
	rightTrigNorm = value / 255.0f;
}

bool GameController::IsButtonDown(unsigned short int button)
{
	if ((this->gamepadState.Gamepad.wButtons & button) == button)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameController::WasButtonPressDetected(unsigned short int button)
{
	if (!(this->gamepadStatePrevious.Gamepad.wButtons & button) && (this->gamepadState.Gamepad.wButtons & button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameController::SetVibration(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION vibration;

	
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	//this sets the values for the vibration
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(0, &vibration);
}

float GameController::getLeftNormalized()
{
	return this->normalizedMagnitude;
}