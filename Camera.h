#pragma once
#include "Object.h"

//
// 카메라도 하나의 오브젝트로 생각함
// 사용 시에는 카메라 게임오브젝트 생성 후 뷰프로젝션 행렬을 업데이트 하는 방식으로 구현
// 카메라 클래스를 상속해서 플레이어에게 붙여 움직이는 카메라도 구현
// 상속의 필요성? 포함을 사용하면 안되는가?
// 오브젝트로 가정하는 목적?
//

class Camera 
	: public Object
{
public:
	Camera(IDirect3DDevice9* device);
	virtual ~Camera();
	
	const D3DXVECTOR3& GetTarget()
	{
		return mTarget;
	}
	void SetUp(D3DXVECTOR3& up)
	{
		mUp = up;
	};
	void SetTarget(D3DXVECTOR3& target)
	{
		mTarget = target;
	};
	const D3DXVECTOR3& GetUp()
	{
		return mUp;
	}

	virtual bool Init(D3DXVECTOR3* position, D3DXVECTOR3* target);
	virtual int Update() override;
	int Destroy() override;

protected:
	IDirect3DDevice9*	mDevice;
	D3DXMATRIX			mViewMatrix;
	D3DXVECTOR3			mUp;
	D3DXVECTOR3			mTarget;

};