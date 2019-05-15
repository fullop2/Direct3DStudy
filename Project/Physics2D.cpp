#include "Physics2D.h"
#include "Gravity2D.h"
#include "Ground.h"

#include "ColliderCircle.h"
#include "Rigidbody2D.h"

Physics2D::Physics2D()
{
}


Physics2D::~Physics2D()
{

}
void Physics2D::AddGround(Ground* grd)
{
	mGrdList.push_back(grd);
}

void Physics2D::AddGraObject(Gravity2D* gravity2D)
{
	mGraList.push_back(gravity2D);
}

void Physics2D::Update()
{
	for (auto ob : mGraList)
	{
		ob->Update(mGrdList);
	}

	for (auto col : mColList)
	{
		col->mbInCollide = false;
		col->mOther = nullptr;
	}
	for (auto col1 : mColList)
	{
		for (auto col2  : mColList)
		{
			if (col1 != col2)
			{
				CollideCheck(col1, col2);
			}
		}
	}

	for (auto rig1 : mRigidList)
	{
		for (auto rig2 : mRigidList)
		{
			if (rig1 == rig2)
			{
				
			}
		}
	}
}

int Physics2D::CollideCheck(ColliderCircle* col1, ColliderCircle* col2)
{
	float dx = col1->mRelativePosition.x - col2->mRelativePosition.x;
	float dy = col1->mRelativePosition.y - col2->mRelativePosition.y;
	float dPosition = dx * dx + dy + dy;
	float dVector = (col1->mRadius + col2->mRadius) * (col1->mRadius + col2->mRadius);
	if (BoundCheck(dPosition, dVector))
	{
		col1->mbInCollide = col2->mbInCollide = true;
		col1->mOther = col2;
		col2->mOther = col1;
	}
	return 0;
}