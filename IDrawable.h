#pragma once
#include "d3d9.h"

class IDrawable
{
	virtual void Draw(IDirect3DDevice9* device) = 0;
};