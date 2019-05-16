#include "stdafx.h"

// external function //
D3DMATERIAL9 InitMtrl(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, float power)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = ambient;
	mtrl.Diffuse = diffuse;
	mtrl.Specular = specular;
	mtrl.Emissive = emissive;
	mtrl.Power = power;
	return mtrl;

}


bool Equals(float lhs, float rhs)
{
	return fabs(lhs - rhs) < EPSILON ? true : false;
}


float GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound)
		return lowBound;

	float f = (rand() % 10000) * 0.0001f;
	return (f * (highBound - lowBound)) + lowBound;
}

void GetRandomVector(D3DXVECTOR3* out, const D3DXVECTOR3* min, const D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

DWORD FtoDw(float f)
{
	return *((DWORD*)& f);
}