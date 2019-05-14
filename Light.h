#pragma once
#include "Object.h"

//
// ���� �ϳ��� ������Ʈ��� ������
// ������Ʈ�� �����ϴ� ����?
//

class Light : public Object
{
public:
	Light();
	virtual ~Light();

	const D3DLIGHT9* GetLight() { return &mLight; };

	bool Init(D3DLIGHTTYPE type, D3DXCOLOR* color, D3DXVECTOR3* direction, D3DXVECTOR3* position);
	int Destroy() override;

private:
	D3DLIGHT9 mLight;
};