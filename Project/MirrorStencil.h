#pragma once
#include "ObjectStencil.h"
class MirrorStencil :
	public ObjectStencil
{
public:
	void Draw(IDirect3DDevice9* device) override;
	MirrorStencil(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer,
		DWORD FVF, int vertexSize, D3DMATERIAL9 * material = nullptr, LPDIRECT3DTEXTURE9 texture = nullptr);
	~MirrorStencil();
};

