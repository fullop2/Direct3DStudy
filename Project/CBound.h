#pragma once
#include "stdafx.h"


class C3DModel;

class CBoundingBox
{
public:
	CBoundingBox();
	CBoundingBox(D3DXVECTOR3 min, D3DXVECTOR3 max)
		:mMin(min), mMax(max)
	{}
	~CBoundingBox();

	bool IsPointInside(D3DXVECTOR3& point);
	const D3DXVECTOR3& GetMin()
	{
		return mMin;
	}
	const D3DXVECTOR3& GetMax()
	{
		return mMax;
	}

private:
	D3DXVECTOR3 mMin;
	D3DXVECTOR3 mMax;
};

class CBoundingSphere
{
public:
	CBoundingSphere();
	CBoundingSphere(D3DXVECTOR3 center, float radius)
		:mCenter(center),mRadius(radius)
	{}
	~CBoundingSphere();

	const D3DXVECTOR3& GetCenter()
	{
		return mCenter;
	}
	const float GetRadius()
	{
		return mRadius;
	}

private:
	D3DXVECTOR3 mCenter;
	float mRadius;

};

bool ComputeBoundingSphere(C3DModel* pModel, CBoundingSphere** ppSphere);
bool ComputeBoundingBox(C3DModel* pModel, CBoundingBox** ppBox);