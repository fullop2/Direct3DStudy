#pragma once
#include "Object.h"
#include "Window.h"
#include "Vertex.h"

class ObjectFactory;
class ObjectManager;

class ObjectBuffer : public Object
{
	friend ObjectFactory;
	friend ObjectManager;

public:
	virtual int Destroy();
	virtual void Draw(LPDIRECT3DDEVICE9& device);
	virtual int Update() override;
	virtual ~ObjectBuffer();

protected:
	ObjectBuffer();
	ObjectBuffer(const ObjectBuffer&);
	ObjectBuffer& operator=(const ObjectBuffer&){}
	

	LPD3DXMESH mMesh;
	IDirect3DVertexBuffer9* mVertexBuffer;
	IDirect3DIndexBuffer9* mIndexBuffer;
	IDirect3DTexture9* mTexture;
	DWORD FVF;
	D3DMATERIAL9 * mMaterial;
	int mVertexBufferSize;
	int mIndexBufferSize;
	int mVertexSize;
};

