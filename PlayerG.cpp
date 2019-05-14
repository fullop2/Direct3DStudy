#include "PlayerG.h"
#include "Window.h"
#include "SceneManager.h"

PlayerG::PlayerG(float height, float width)
	:Gravity2D(height,width)
{
}


PlayerG::~PlayerG()
{
}

bool PlayerG::Falling()
{
	if (mVelocity.y > 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerG::Update(vector<Ground*> grounds)
{
	if (mbStayGround && GetKeyDown('W'))
	{
		mVelocity.y = -18.0f;
		mbStayGround = false;
	}
	else if (mbStayGround &&GetKeyDown('S'))
	{
		mPosition.y += 2.0f;

		mbStayGround = false;
	}
	if (GetKeyDown('A'))
	{
		mVelocity.x = -5.0f;
		mbStayGround = false;
	}
	else if (GetKeyDown('D'))
	{
		mVelocity.x = 5.0f;
		mbStayGround = false;
	}
	else
	{
		mVelocity.x = 0.0f;
	}
	
	for (auto ground : grounds)
	{
		if (GetIsKinetic()&& InGroundCheck(ground) && !mbStayGround)
			{
				mbStayGround = true;
			}
	}
	if (GetIsKinetic())
	{
		if (mbStayGround && Falling())
		{
			mVelocity.y = 0.0f;
		}
		else
		{
			GravityForce();
		}
		Acceleration();
	}
	if (mPosition.y > 700)
	{
		SceneManager::Get()->EndScene();
	}

	return true;
}