#include "ObjectBuffer.h"

//
// for study
//

ObjectBuffer::ObjectBuffer()
:mMesh(nullptr)
{
}

ObjectBuffer::~ObjectBuffer()
{
}

int ObjectBuffer::Update()
{
	/*
	if (mRotation.y > 360.0f)
	{
	mRotation.y = 0;
	}
	else
	{
	mRotation.y += 1.0f;
	}
	
	if (mMesh)
	{
		float& dif = mMaterial->Diffuse.a;
		if (GetKeyDown('A') && dif > 0.0f)
			dif -= 0.01f;
		if (GetKeyDown('S') && dif < 1.0f)
			dif += 0.01f;
	}*/
	return true;
}


int ObjectBuffer::Destroy()
{
	SAFE_RELEASE(mVertexBuffer);
	SAFE_RELEASE(mIndexBuffer);
	SAFE_DELETE(mMaterial);
	SAFE_RELEASE(mTexture);
	SAFE_RELEASE(mMesh);
	return true;
}

void ObjectBuffer::Draw(LPDIRECT3DDEVICE9& device)
{
	if (mMesh)
	{
		device->SetMaterial(mMaterial);
		device->SetTexture(0, 0);
		mMesh->DrawSubset(0);
	}
	else
	{
		device->SetStreamSource(0, mVertexBuffer, 0, mVertexSize);
		device->SetFVF(FVF);
		if (mMaterial)
		{
			device->SetMaterial(mMaterial);
		}
		if (mTexture)
		{
			device->SetTexture(0, mTexture);
		}
		if (mIndexBuffer)
		{
			device->SetIndices(mIndexBuffer);
			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
				0, 0, mVertexBufferSize, 0, mIndexBufferSize / 3);
		}
		else
		{
			device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, mVertexBufferSize / 3);
		}
	}
}