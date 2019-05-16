#pragma once
#include "stdafx.h"

class Light
{
public:
	Light();
	virtual ~Light();

	const D3DLIGHT9* GetLight() { return &mLight; };

	bool Init(D3DLIGHTTYPE type, D3DXCOLOR* color, D3DXVECTOR3* direction, D3DXVECTOR3* position);
	int Destroy();

private:
	D3DXVECTOR3 mPosition;
	D3DLIGHT9 mLight;
};