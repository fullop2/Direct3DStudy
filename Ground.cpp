#include "Ground.h"
#include "Physics2D.h"


Ground::Ground(float width, float height)
{
	mWidth = width;
	mHeight = height;
	Physics2D::Get()->AddGround(this);
}


Ground::~Ground()
{
}
