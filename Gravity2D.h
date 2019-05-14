#pragma once
#include "Object2D.h"

class Ground;
class Gravity2D
	:public Object2D
{
public:

	virtual bool Update(vector<Ground*>);
	bool InGroundCheck(Ground*);
	bool GetIsKinetic() { return mbIsKinetic; }
	void Acceleration();
	void GravityForce();
	virtual bool Falling() { return false; };
	
	Gravity2D(float height, float width);
	virtual ~Gravity2D();

protected:
	float mGravity;
	float mHeight;
	float mWidth;
	bool mbIsKinetic;
	bool mbStayGround;
	D3DXVECTOR2 mVelocity;
};