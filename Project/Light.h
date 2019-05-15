#pragma once
#include "Object.h"

//
// 조명도 하나의 오브젝트라고 생각함
// 오브젝트로 가정하는 목적?
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