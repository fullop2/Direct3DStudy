#include "Camera.h"
#include "Window.h"

Camera::Camera(IDirect3DDevice9* device)
	:mDevice(device)
{
}


Camera::~Camera()
{
	
}

bool Camera::Init(D3DXVECTOR3* position, D3DXVECTOR3* target)
{
	mPosition = *position;
	mTarget = *target;
	mUp = D3DXVECTOR3(0, 1.0f, 0);
	Update();

	return true;
}

int Camera::Update()
{	

	if (GetKeyDown('I'))
		mPosition.y += 20;

	if (GetKeyDown('O'))
		mPosition.y -= 20;


	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &mPosition, &mTarget, &mUp);
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

int Camera::Destroy()
{
	return true;
}