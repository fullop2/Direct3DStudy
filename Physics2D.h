#pragma once
#include "stdafx.h"

class Gravity2D;
class Ground;
class ColliderCircle;
class Rigidbody2D;

class Physics2D
{
public:
	void Update();
	Physics2D();
	~Physics2D();

	static Physics2D* Get()
	{
		static Physics2D ins;
		return &ins;
	}
	void AddGround(Ground*);
	void AddGraObject(Gravity2D*);

private:
	vector<Gravity2D*> mGraList;
	vector<Ground*> mGrdList;
	vector<ColliderCircle*> mColList;
	vector<Rigidbody2D*> mRigidList;

	int CollideCheck(ColliderCircle* col1, ColliderCircle* col2);

	const bool BoundCheck(float deltaPosition, float sumRadius) 
	{
		return sumRadius - deltaPosition >= 0.0f;
	}
};

namespace
{
	
}