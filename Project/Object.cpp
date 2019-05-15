#include "Object.h"

Object::Object()
{
	mTag = "";
	mPosition = D3DXVECTOR3(0, 0, 0);
	mRotation = D3DXVECTOR3(0, 0, 0);
	mScale = D3DXVECTOR3(1,1,1);
	mbAvailable = true;
}

void Object::Move(D3DXVECTOR3 position)
{
	Move(position.x, position.y, position.z);
}

void Object::Move(float x, float y, float z)
{

	this->mPosition.x = x;
	this->mPosition.y = y;
	this->mPosition.z = z;
}

void Object::MoveRelative(D3DXVECTOR3 displacement)
{
	MoveRelative(displacement.x, displacement.y, displacement.z);
}

void Object::MoveRelative(float x, float y, float z)
{
	this->mPosition.x += x;
	this->mPosition.y += y;
	this->mPosition.z += z;
}

void Object::Rotate(D3DXVECTOR3 rotation)
{
	Rotate(rotation.x, rotation.y, rotation.z);
}

void Object::Rotate(float x, float y, float z)
{
	this->mRotation.x += x;
	this->mRotation.y += y;
	this->mRotation.z += z;

}

void Object::SetScale(D3DXVECTOR3 scale)
{
	this->mScale = scale;
}