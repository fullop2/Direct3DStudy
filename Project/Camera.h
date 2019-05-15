#pragma once
#include "Object.h"

//
// ī�޶� �ϳ��� ������Ʈ�� ������
// ��� �ÿ��� ī�޶� ���ӿ�����Ʈ ���� �� ���������� ����� ������Ʈ �ϴ� ������� ����
// ī�޶� Ŭ������ ����ؼ� �÷��̾�� �ٿ� �����̴� ī�޶� ����
// ����� �ʿ伺? ������ ����ϸ� �ȵǴ°�?
// ������Ʈ�� �����ϴ� ����?
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