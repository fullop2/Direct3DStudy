#pragma once
#include "Camera.h"
class FlexCamera :
	public Camera
{
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };

	void strafe(float units);
	void fly(float units);
	void walk(float units);

	void pitch(float angle);
	void yaw(float angle);
	void roll(float angle);

	void getViewMatrix(D3DXMATRIX* V);
	/*
	void setCameraType(CameraType cameraType);
	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
*/

	FlexCamera(IDirect3DDevice9* device);
	~FlexCamera();

	int Update() override;
private:

	CameraType mCameraType;
	D3DXVECTOR3 mRight;
	D3DXVECTOR3 mLook;
};

namespace
{
	const D3DXVECTOR3 WORLD_UP = D3DXVECTOR3{ 0.0f,1.0f,0.0f };
}


