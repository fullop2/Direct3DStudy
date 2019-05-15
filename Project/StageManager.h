#pragma once
#include "stdafx.h"
#include "Object3D.h"

class StageManager
{
private:
	StageManager();
	~StageManager();

public:

public:
	static StageManager& getInstance();
	void Update();
};


