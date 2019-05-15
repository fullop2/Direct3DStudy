#include "RigidBody.h"



RigidBody::RigidBody(D3DXVECTOR3& position, float mass)
	:mPosition(position),mbFunctional(true)
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::AddForce(D3DXVECTOR3& force)
{
	mAcceleration += force / mMass;
}

bool RigidBody::Update()
{
	if (!mbFunctional)
	{
		mPosition += mAcceleration;
	}
	return true;
}

RigidSphere::RigidSphere(D3DXVECTOR3& position, float radius, float mass)
	:RigidBody(position,mass)
{
}

RigidBox::RigidBox(D3DXVECTOR3& position, D3DXVECTOR3& vertex1, D3DXVECTOR3& vertex2, float mass)
	:RigidBody(position, mass),mVertex1(vertex1),mVertex2(vertex2)
{
}
