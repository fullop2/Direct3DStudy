#include "Rigidbody2D.h"
#include "Object2D.h"
#include "Collider2D.h"


Rigidbody2D::Rigidbody2D(Object2D* object, Collider2D* collider)
	:mRelPosition(object->mPosition),mbInCollision(&(collider->mbInCollide))
{
}


Rigidbody2D::~Rigidbody2D()
{
}

int Rigidbody2D::Update()
{
	return 1;
}