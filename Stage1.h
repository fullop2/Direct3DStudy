#pragma once
#include "Scene.h"
class Stage1 :
	public Scene
{
public:
	Stage1(Renderer* renderer);
	virtual ~Stage1();

	bool Init() override;
};

