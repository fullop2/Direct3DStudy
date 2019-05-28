#pragma once
#include "stdafx.h"

// obj loader teset
#include "MeshLoader.h"

class Renderer;
class Object3D;

// 시간 : 18.08.12 17:21
// mtrl, tex등 멤버의 형태, getter, setter 수정 필요

class C3DModel
{
	friend Renderer;
	friend Object3D;
public:
	C3DModel();
	C3DModel(ID3DXBaseMesh* mesh, vector<D3DMATERIAL9>* mtrls = nullptr, vector<IDirect3DTexture9*>* textures = nullptr,
		ID3DXBuffer* adjacency = nullptr, vector<pair<D3DRENDERSTATETYPE, DWORD>>* renderState = nullptr);
	C3DModel(LPCSTR name);
	~C3DModel()
	{
		Destroy();
	};

	void GetMesh(LPD3DXMESH* ppMesh)
	{
		*ppMesh = (LPD3DXMESH)mMesh;
	}
	/*
	void SetMesh(ID3DXMesh * pMesh)
	{
		SAFE_RELEASE(mMesh);
		mMesh = pMesh;
	}*/

	void GetAdjacency(LPD3DXBUFFER* ppBuffer)
	{
		*ppBuffer = mAdjacency;
	}
	void SetRenderState(vector<pair<D3DRENDERSTATETYPE, DWORD>>* pRenderState)
	{
		mRenderState = pRenderState;
	}

	void Draw(IDirect3DDevice9* device);
	int Destroy();
private:

	static MeshLoader loader;
	ID3DXBaseMesh* mMesh;
	MtrlVec* mMtrls;
	TexVec* mTextures;
	vector<pair<D3DRENDERSTATETYPE, DWORD>>* mRenderState;
	DWORD mNumSubsets;
	ID3DXBuffer* mAdjacency;
};