#pragma once
#include "stdafx.h"

class Rigidbody2D;
class Object2D;

class Collider2D
{
	friend Rigidbody2D;
public:
	Collider2D(Object2D* object);
	virtual ~Collider2D();
protected:
	bool mbInCollide;
	bool mbFunctional;
	D3DXVECTOR3& mRelativePosition;
	Collider2D* mOther;

};

