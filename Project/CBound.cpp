#include "CBound.h"
#include "C3DModel.h"


CBoundingBox::CBoundingBox()
{
	mMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	mMax = -mMin;
}


CBoundingBox::~CBoundingBox()
{
}

bool CBoundingBox::IsPointInside(D3DXVECTOR3& point)
{
	if ((point.x >= mMin.x && point.y >= mMin.y &&point.z >= mMin.z) &&
		point.x <= mMax.x && point.y <= mMax.y &&point.z <= mMax.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CBoundingSphere::CBoundingSphere()
{
	mRadius = 0.0f;
}


CBoundingSphere::~CBoundingSphere()
{
}

bool ComputeBoundingSphere(C3DModel* pModel, CBoundingSphere** ppSphere)
{
	
	ID3DXMesh* pMesh = nullptr;
	pModel->GetMesh(&pMesh);

	HRESULT hr = 0;
	BYTE * v = nullptr;
	D3DXVECTOR3 center(0, 0, 0);
	float radius = 0.0f;

	pMesh->LockVertexBuffer(0, (void**)&v);
	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)v, pMesh->GetNumVertices(), 
		D3DXGetFVFVertexSize(pMesh->GetFVF()), &center, &radius);
	pMesh->UnlockVertexBuffer();
	
	*ppSphere = new CBoundingSphere(center, radius);

	if (FAILED(hr))
	{
		return false;
	}
	return true;

}

bool ComputeBoundingBox(C3DModel* pModel, CBoundingBox** ppBox)
{
	ID3DXMesh* pMesh = nullptr;
	pModel->GetMesh(&pMesh);

	HRESULT hr = 0;
	BYTE* v = nullptr;
	D3DXVECTOR3 mmin(0,0,0), mmax(0,0,0);

	pMesh->LockVertexBuffer(0, (void**)&v);
	hr = D3DXComputeBoundingBox((D3DXVECTOR3*)v, pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->GetFVF()), &mmin, &mmax);
	pMesh->UnlockVertexBuffer();

	*ppBox = new CBoundingBox(mmin, mmax);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}