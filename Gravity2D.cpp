#include "Gravity2D.h"
#include "Ground.h"
#include "Physics2D.h"
#include "Window.h"

Gravity2D::Gravity2D(float height, float width)
	:mVelocity(D3DXVECTOR2{ 0,0}), mbIsKinetic(true),mGravity(-1.0f),mbStayGround(false),mHeight(height),mWidth(width)
{
	Physics2D::Get()->AddGraObject(this);
}


Gravity2D::~Gravity2D()
{
}

void Gravity2D::GravityForce()
{
	if(!mbStayGround)
	mVelocity.y -= mGravity;
}

void Gravity2D::Acceleration()
{
	mPosition.x += mVelocity.x;
	mPosition.y += mVelocity.y;
}

bool Gravity2D::InGroundCheck(Ground* ground)
{
	int grdHeight = static_cast<int>(ground->GetHeight() * ground->GetScale().y);
	int grdWidth = static_cast<int>(ground->GetWidth() * ground->GetScale().x);
	
	float feet = mPosition.y + mHeight / 2;
	float top = ground->GetPosition().y - grdHeight / 2;
	float left = ground->GetPosition().x + grdWidth / 2;
	float right = ground->GetPosition().x - grdWidth / 2;

	if (feet + mVelocity.y >= top - 0.001f && top >= feet - 0.001f &&
		right <= mPosition.x && mPosition.x <= left)
	{
		mPosition.y = top-mHeight/2;
		return true;
	}
	else
		return false;
}

bool Gravity2D::Update(vector<Ground*> grounds)
{
	mbStayGround = false;

	for (auto ground : grounds)
	{
		if (InGroundCheck(ground))
		{
			mbStayGround = true;
			break;
		}
	}

	GravityForce();
	Acceleration();

	return true;
}