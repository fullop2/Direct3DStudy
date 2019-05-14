#pragma once
#include "stdafx.h"

class Collider2D;
class Physics2D;
class Object2D;

class Rigidbody2D
{
	friend Physics2D;
public:
	Rigidbody2D(Object2D* object, Collider2D* collider = nullptr);
	~Rigidbody2D();
	int Update();
private:
	bool mbIsKinetic;
	bool* mbInCollision;
	D3DXVECTOR3& mRelPosition;
	D3DXVECTOR3 mVelocity;
	float mWeight;
	float mCOR; // coefficient of restitution : 반발계수
};

