#pragma once
#include "ObjectBuffer.h"
class ObjectStencil :
	public ObjectBuffer
{
public:
	ObjectStencil(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
		LPDIRECT3DINDEXBUFFER9 indexBuffer,
		DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture);
	ObjectStencil(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture);
	virtual void Draw(LPDIRECT3DDEVICE9& device) override = 0;
protected:
	
	
};

