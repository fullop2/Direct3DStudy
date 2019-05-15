#include "FlexCamera.h"
#include "Window.h"
#include "Timer.h"

static const D3DXVECTOR3 WORLD_UP = D3DXVECTOR3{ 0.0f,1.0f,0.0f };

FlexCamera::FlexCamera(IDirect3DDevice9* device)
	:Camera(device),mCameraType(AIRCRAFT),mLook(D3DXVECTOR3{ 0,-1000,0 }),mRight(D3DXVECTOR3{1.0f,0.0f,0.0f})
{
	mUp = D3DXVECTOR3{ 0.0f,1.0f,0.0f };
	mPosition = D3DXVECTOR3(0, 1000, 0);
}


FlexCamera::~FlexCamera()
{
}

void FlexCamera::getViewMatrix(D3DXMATRIX* V)
{
	D3DXVec3Normalize(&mLook, &mLook);

	D3DXVec3Cross(&mUp, &mLook, &mRight);
	D3DXVec3Normalize(&mUp, &mUp);

	D3DXVec3Cross(&mRight, &mUp, &mLook);
	D3DXVec3Normalize(&mRight, &mRight);

	float x = -D3DXVec3Dot(&mRight, &mPosition);
	float y = -D3DXVec3Dot(&mUp, &mPosition);
	float z = -D3DXVec3Dot(&mLook, &mPosition);

	(*V)(0, 0) = mRight.x; (*V)(0, 1) = mUp.x; (*V)(0, 2) = mLook.x; (*V)(0, 3) = 0.0f;
	(*V)(1, 0) = mRight.y; (*V)(1, 1) = mUp.y; (*V)(1, 2) = mLook.y; (*V)(1, 3) = 0.0f;
	(*V)(2, 0) = mRight.z; (*V)(2, 1) = mUp.z; (*V)(2, 2) = mLook.z; (*V)(2, 3) = 0.0f;
	(*V)(3, 0) = x;		   (*V)(3, 1) = y;	   (*V)(3, 2) = z;		 (*V)(3, 3) = 1.0f;
}

void FlexCamera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &mRight, angle);

	D3DXVec3TransformCoord(&mUp, &mUp, &T);
	D3DXVec3TransformCoord(&mLook, &mLook, &T);
}

void FlexCamera::yaw(float angle)
{
	D3DXMATRIX T;
	
	if (mCameraType == LANDOBJECT)
	{
		D3DXMatrixRotationY(&T, angle);
	}
	if (mCameraType == AIRCRAFT)
	{
		D3DXMatrixRotationAxis(&T, &mUp, angle);
	}

	D3DXVec3TransformCoord(&mRight, &mRight, &T);
	D3DXVec3TransformCoord(&mLook, &mLook, &T);
}

void FlexCamera::roll(float angle)
{
	if (mCameraType == AIRCRAFT)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &mLook, angle);

		D3DXVec3TransformCoord(&mRight, &mRight, &T);
		D3DXVec3TransformCoord(&mUp, &mUp, &T);
	}
}

void FlexCamera::walk(float units)
{
	if (units == 0)
	{
		return;
	}
	if (mCameraType == LANDOBJECT)
	{
		D3DXVECTOR3 dir;
		D3DXVec3Cross(&dir, &mRight, &::WORLD_UP);
		mPosition += D3DXVECTOR3(dir.x, 0.0f, dir.z) * units;
	}
	if (mCameraType == AIRCRAFT)
	{
		mPosition += mLook * units;
	}
}

void FlexCamera::strafe(float units)
{
	if (mCameraType == LANDOBJECT)
	{
		mPosition += D3DXVECTOR3(mRight.x, 0.0f, mRight.z) * units;
	}
	if (mCameraType == AIRCRAFT)
	{
		mPosition += mRight * units;
	}
}

void FlexCamera::fly(float units)
{
	if (mCameraType == AIRCRAFT)
	{
		mPosition += mUp * units;
	}
}

int FlexCamera::Update()
{
	static float speed = 1.0f * Timer::Get().GetTime() / 100;
	static bool pushed = false;
	if (!pushed && GetKeyDown(16))
	{
		speed = speed *0.5f;
		pushed = true;
	}
	else if(pushed && GetKeyDown(16))
	{
		speed = speed * 2.0f;
		pushed = false;
	}

	if (GetKeyDown('W'))
		walk(speed);

	if (GetKeyDown('S'))
		walk(-speed);

	if (GetKeyDown('A'))
		strafe(-speed);

	if (GetKeyDown('D'))
		strafe(speed);

	if (GetKeyDown('R'))
		fly(speed);

	if (GetKeyDown('F'))
		fly(-speed);

	speed *= 0.05f;
	if (GetKeyDown(38))
		pitch(speed);

	if (GetKeyDown(40))
		pitch(-speed);

	if (GetKeyDown(37))
		yaw(-speed);

	if (GetKeyDown(39))
		yaw(speed);

	if (GetKeyDown('N'))
		roll(speed );

	if (GetKeyDown('M'))
		roll(-speed);
	speed *= 20.0f;
	D3DXMATRIX V;
	getViewMatrix(&V);
	mDevice->SetTransform(D3DTS_VIEW, &V);

	// setting projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI / 4.0f, // 45 - degree
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		1000.0f);
	mDevice->SetTransform(D3DTS_PROJECTION, &proj);


	return true;
}