#pragma once
#include "Object3D.h"
#include "Window.h"
#include "Vertex.h"

class ObjectFactory;
class ObjectManager;

class ObjectBuffer : public Object3D
{
	friend ObjectFactory;
	friend ObjectManager;

public:	
	ObjectBuffer(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
		LPDIRECT3DINDEXBUFFER9 indexBuffer,
		DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture);
	ObjectBuffer::ObjectBuffer(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture);
	virtual int Destroy() override;
	virtual void Draw(LPDIRECT3DDEVICE9& device);
	virtual int Update() override;
	virtual ~ObjectBuffer();

protected:
	LPD3DXMESH mMesh;
	IDirect3DVertexBuffer9* mVertexBuffer;
	IDirect3DIndexBuffer9* mIndexBuffer;
	IDirect3DTexture9* mTexture;
	DWORD FVF;
	D3DMATERIAL9 mMaterial;
	int mVertexBufferSize;
	int mIndexBufferSize;
	int mVertexSize;
};

