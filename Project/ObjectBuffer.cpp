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

int ObjectBuffer::Destroy()
{
	SAFE_RELEASE(mVertexBuffer);
	SAFE_RELEASE(mIndexBuffer);
	SAFE_RELEASE(mTexture);
	SAFE_RELEASE(mMesh);
	return true;
}

void ObjectBuffer::Draw(IDirect3DDevice9* device)
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