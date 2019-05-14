#include "Collider2D.h"
#include "Object2D.h"


Collider2D::Collider2D(Object2D* object)
	:mbInCollide(false), mbFunctional(false), mRelativePosition(object->mPosition),mOther(nullptr)
{
}


Collider2D::~Collider2D()
{
}
