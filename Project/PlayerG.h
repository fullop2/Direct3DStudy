#pragma once
#include "Gravity2D.h"

class PlayerG :
	public Gravity2D
{
public:
	PlayerG(float height, float width);
	~PlayerG();
	bool Falling() override;
	bool Update(vector<Ground*>) override;
};

