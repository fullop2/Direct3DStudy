#pragma once
#include "Object2D.h"
class Player :
	public Object2D
{
private:

public:
	Player();
	~Player();
	int Update() override;
};