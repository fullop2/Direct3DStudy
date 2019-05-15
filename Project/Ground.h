#pragma once
#include "Object2D.h"
class Ground :
	public Object2D
{
public:
	float GetWidth() { return mWidth; }
	float GetHeight() { return mHeight; }
	
	Ground(float width,float height);
	virtual ~Ground();

private:
	float mWidth;
	float mHeight;
};

