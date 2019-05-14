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