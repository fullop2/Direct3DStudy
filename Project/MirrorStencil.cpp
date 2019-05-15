#include "MirrorStencil.h"



MirrorStencil::MirrorStencil(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
	LPDIRECT3DINDEXBUFFER9 indexBuffer,
	DWORD FVF, int vertexSize, D3DMATERIAL9 * material, LPDIRECT3DTEXTURE9 texture)
{
	mMesh = nullptr;
	mVertexBuffer = vertexBuffer;
	mIndexBuffer = indexBuffer;
	FVF = FVF;
	mVertexSize = vertexSize;
	mMaterial = material;
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


MirrorStencil::~MirrorStencil()
{
}

void MirrorStencil::Draw(LPDIRECT3DDEVICE9& device) 
{/*
 
	//
	// Draw Mirror quad to stencil buffer ONLY.  In this way
	// only the stencil bits that correspond to the mirror will
	// be on.  Therefore, the reflected teapot can only be rendered
	// where the stencil bits are turned on, and thus on the mirror 
	// only.
	//

	device->SetRenderState(D3DRS_STENCILENABLE, true);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILREF, 0x1);
	device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// disable writes to the depth and back buffers
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	////////////////////////////////////////////////////////////////////////////////////////////////

	// draw the mirror to the stencil buffer
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(Vertex));
	device->SetFVF(TVertex::FVF);
	device->SetMaterial(mMaterial);
	device->SetTexture(0, mTexture);

	device->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// re-enable depth writes
	device->SetRenderState(D3DRS_ZWRITEENABLE, true);



	////////////////////////////////////////////////////////////////////////////////////////
	// only draw reflected teapot to the pixels where the mirror
	// was drawn to.
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// position reflection
	D3DXMATRIX W, T, R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);

	D3DXMatrixTranslation(&T,
		TeapotPosition.x,
		TeapotPosition.y,
		TeapotPosition.z);

	W = T * R;

	// clear depth buffer and blend the reflected teapot with the mirror
	device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	// Finally, draw the reflected teapot
	device->SetTransform(D3DTS_WORLD, &W);
	device->SetMaterial(&TeapotMtrl);
	device->SetTexture(0, 0);

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	device->DrawSubset(0);

	// Restore render states.
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_STENCILENABLE, false);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	*/
}