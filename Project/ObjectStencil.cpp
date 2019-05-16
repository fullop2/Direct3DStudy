#include "ObjectStencil.h"

ObjectStencil::ObjectStencil(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
	LPDIRECT3DINDEXBUFFER9 indexBuffer,
	DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture)
	:ObjectBuffer(vertexBuffer,indexBuffer,FVF,vertexSize,material,texture)
{

}
ObjectStencil::ObjectStencil(LPD3DXMESH mesh, D3DMATERIAL9* mtrl, LPDIRECT3DTEXTURE9 texture)
	:ObjectBuffer(mesh,mtrl,texture)
{

}