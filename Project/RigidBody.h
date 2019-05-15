#pragma once
#include "stdafx.h"

// 
// 2D 개발용 임시 강체 구현
//

class RigidBody
{
public:
	//interface
	void AddForce(D3DXVECTOR3& force);
	bool Update();

	// getter,setter
	void SetMass(float mass) {	mMass = mass;}
	void SetAcceleration(D3DXVECTOR3& acceleration) { mAcceleration = acceleration; }
	const float GetMass() { return mMass; }
	const D3DXVECTOR3 GetAcceleration() { return mAcceleration; }

	// ctr,dtr
	RigidBody(D3DXVECTOR3& position, float mass = 1);
	~RigidBody();

protected:
	bool mbFunctional;
	D3DXVECTOR3& mPosition;
	D3DXVECTOR3 mAcceleration;
	float mMass;
	
};

class RigidSphere
	: public RigidBody
{
public:
	RigidSphere(D3DXVECTOR3& position, float radius, float mass = 1);

private:
	float mRadius;
};

class RigidBox
	: public RigidBody
{
public:
	RigidBox(D3DXVECTOR3& position, D3DXVECTOR3& vertex1, D3DXVECTOR3& vertex2, float mass = 1);
private:
	D3DXVECTOR3 mVertex1, mVertex2;
};