#pragma once
#include "SimpleMath.h"
#include "GameController.h"
class BackgroundGenerator
{
public:
	BackgroundGenerator();
	~BackgroundGenerator();

private:
	float red;
	float green;
	float blue;

public:
	DirectX::SimpleMath::Color Update(std::shared_ptr<GameController> controller);
};

