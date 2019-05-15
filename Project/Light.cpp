#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
	Destroy();
}

bool Light::Init(D3DLIGHTTYPE type, D3DXCOLOR* color, D3DXVECTOR3* direction, D3DXVECTOR3* position)
{
	ZeroMemory(&mLight, sizeof(mLight));
	mLight.Type = type;
	mLight.Diffuse = *color;					// 난반사광	- 특정한 방향으로 진행, 표면에 닿으면 모든 방향으로 동일하게 반사
	mLight.Specular = *color * .2f;				// 정반사광	- 특정한 방향으로 진행, 표면에 닿으면 한 방향으로 강하게 반사2
	mLight.Ambient = *color * .6f;				// 환경광 - 다른 표면에 반사되어 전반적인 장면을 밝게 하는 빛


	// 방향성, 스폿 광원인 경우
	if (type != D3DLIGHT_POINT)
	{
		mLight.Direction = *direction;
	}

	// 점, 스폿 광원인 경우
	if (type != D3DLIGHT_DIRECTIONAL)
	{
		mLight.Position = *position;
		mLight.Range = 20.0f;
		mLight.Attenuation0 = 0.0f;
		mLight.Attenuation1 = 0.125f;
		mLight.Attenuation2 = 0.0f;
	}

	// 스폿 광원인 경우
	if (type == D3DLIGHT_SPOT)
	{
		mLight.Phi = D3DXToRadian(40.0f);
		mLight.Theta = D3DXToRadian(20.0f);
		mLight.Falloff = 1.0f;
	}

	return true;
}

int Light::Destroy()
{
	return true;
}