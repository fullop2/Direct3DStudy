#include "ObjectBuffer.h"

//
// for study
//

ObjectBuffer::ObjectBuffer(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
	LPDIRECT3DINDEXBUFFER9 indexBuffer,
	DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture)
{
	mMesh = nullptr;
	mVertexBuffer = vertexBuffer;
	mIndexBuffer = indexBuffer;
	FVF = FVF;
	mVertexSize = vertexSize;
	mMaterial = *material;
	mTexture = texture;

	if (vertexBuffer)
	{
		D3DVERTEXBUFFER_DESC vdesc;
		vertexBuffer->GetDesc(&vdesc);
		mVertexBufferSize = vdesc.Size;
	}
	if (indexBuffer)
	{
		D3DINDEXBUFFER_DESC idesc;
		indexBuffer->GetDesc(&idesc);
		mIndexBufferSize = idesc.Size;
	}

}
ObjectBuffer::ObjectBuffer(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture)
{
	mMesh = mesh;
	mMaterial = *mtrl;
	mTexture = texture;
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;
	FVF = 0;
	mVertexSize = 0;
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
	SAFE_RELEASE(mTexture);
	SAFE_RELEASE(mMesh);
	return true;
}

void ObjectBuffer::Draw(LPDIRECT3DDEVICE9& device)
{
	if (mMesh)
	{
		device->SetMaterial(&mMaterial);
		device->SetTexture(0, 0);
		mMesh->DrawSubset(0);
	}
	else
	{
		device->SetStreamSource(0, mVertexBuffer, 0, mVertexSize);
		device->SetFVF(FVF);
		if (&mMaterial)
		{
			device->SetMaterial(&mMaterial);
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