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
	ObjectBuffer();
	ObjectBuffer(const ObjectBuffer&);
	virtual int Destroy() override;
	virtual void Draw(LPDIRECT3DDEVICE9& device);
	virtual int Update() override;
	virtual ~ObjectBuffer();

protected:


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

