#pragma once
#include "ObjectStencil.h"
#include "Renderer.h"

class ObjectFactory
{
public:
	ObjectBuffer * CreateVertex(
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer,
		DWORD FVF, int vertexSize, D3DMATERIAL9 * material = nullptr, LPDIRECT3DTEXTURE9 texture = nullptr);
	ObjectBuffer* CreateMesh(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture = nullptr);

	ObjectFactory(LPDIRECT3DDEVICE9 device)
		:mDevice(device)
	{}
private:
	LPDIRECT3DDEVICE9 mDevice;
};