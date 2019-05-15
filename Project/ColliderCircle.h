#pragma once
#include "Collider2D.h"

class Physics2D;

class ColliderCircle :
	public Collider2D
{
	friend Physics2D;
public:
	ColliderCircle(D3DXVECTOR3 relativePosition = D3DXVECTOR3{});
	~ColliderCircle();
	
protected:
	float mRadius;
};

