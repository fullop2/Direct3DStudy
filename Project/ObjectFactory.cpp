#include "ObjectFactory.h"

ObjectBuffer* ObjectFactory::CreateVertex(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
	LPDIRECT3DINDEXBUFFER9 indexBuffer,
	DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture)
{
	ObjectBuffer* objectBuffer = new ObjectBuffer();

	objectBuffer->mMesh = nullptr;
	objectBuffer->mVertexBuffer = vertexBuffer;
	objectBuffer->mIndexBuffer = indexBuffer;
	objectBuffer->FVF = FVF;
	objectBuffer->mVertexSize = vertexSize;
	objectBuffer->mMaterial = material;
	objectBuffer->mTexture = texture;

	if (vertexBuffer)
	{
		D3DVERTEXBUFFER_DESC vdesc;
		vertexBuffer->GetDesc(&vdesc);
		objectBuffer->mVertexBufferSize = vdesc.Size;
	}
	if (indexBuffer)
	{
		D3DINDEXBUFFER_DESC idesc;
		indexBuffer->GetDesc(&idesc);
		objectBuffer->mIndexBufferSize = idesc.Size;
	}
	return objectBuffer;
};

ObjectBuffer* ObjectFactory::CreateMesh(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture)
{
	ObjectBuffer* objectBuffer = new ObjectBuffer();

	objectBuffer->mMesh = mesh;
	objectBuffer->mMaterial = mtrl;
	objectBuffer->mTexture = texture;
	objectBuffer->mVertexBuffer = nullptr;
	objectBuffer->mIndexBuffer = nullptr;
	objectBuffer->FVF = 0;
	objectBuffer->mVertexSize = 0;

	return objectBuffer;
}