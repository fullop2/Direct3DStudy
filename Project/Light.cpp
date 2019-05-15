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
	mLight.Diffuse = *color;					// ���ݻ籤	- Ư���� �������� ����, ǥ�鿡 ������ ��� �������� �����ϰ� �ݻ�
	mLight.Specular = *color * .2f;				// ���ݻ籤	- Ư���� �������� ����, ǥ�鿡 ������ �� �������� ���ϰ� �ݻ�2
	mLight.Ambient = *color * .6f;				// ȯ�汤 - �ٸ� ǥ�鿡 �ݻ�Ǿ� �������� ����� ��� �ϴ� ��


	// ���⼺, ���� ������ ���
	if (type != D3DLIGHT_POINT)
	{
		mLight.Direction = *direction;
	}

	// ��, ���� ������ ���
	if (type != D3DLIGHT_DIRECTIONAL)
	{
		mLight.Position = *position;
		mLight.Range = 20.0f;
		mLight.Attenuation0 = 0.0f;
		mLight.Attenuation1 = 0.125f;
		mLight.Attenuation2 = 0.0f;
	}

	// ���� ������ ���
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