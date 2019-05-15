#pragma once
#include "Scene.h"

class Stage_Main :
	public Scene
{
private:


public:
	Stage_Main(Renderer* renderer);
	~Stage_Main();

	bool Init() override;
};

