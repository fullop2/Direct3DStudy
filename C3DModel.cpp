#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "C3DModel.h"


C3DModel::C3DModel()
{
	mMesh = nullptr;
	mMtrls = new MtrlVec;
	mTextures = new TexVec;
	mAdjacency = 0;
	mRenderState = nullptr;
};

C3DModel::C3DModel(ID3DXBaseMesh* mesh, vector<D3DMATERIAL9>* mtrls, vector<IDirect3DTexture9*>* textures, 
	ID3DXBuffer* adjacency, vector<pair<D3DRENDERSTATETYPE, DWORD>>* renderState)
	:mMesh(mesh)
{
	mMesh->GetAttributeTable(nullptr, &mNumSubsets);
	if (!mNumSubsets)
		mNumSubsets = 1;

	mAdjacency = adjacency;

	if (mtrls)
	{
		mMtrls = mtrls;
	}
	else
	{
		mMtrls = new MtrlVec;
		for(size_t a  = 0 ; a < mNumSubsets; ++a)
		mMtrls->push_back(D3DMATERIAL9(RED_MTRL));
	}
	if (textures)
	{
		mTextures = textures;
	}
	else
	{
		mTextures = new TexVec;
		for (size_t a = 0; a < mNumSubsets; ++a)
		mTextures->push_back(nullptr);
	}
	mRenderState = renderState;
}

C3DModel::C3DModel(LPCSTR name)
{
	/*
	std::ifstream inFile;
	inFile.open(name);
	std::string line;
	std::stringstream lins;
	inFile >> line;
	lins.str(line);
	string tmp;
	lins >> tmp;
	lins >> tmp;
	*/
}

void C3DModel::Draw(IDirect3DDevice9* device)
{
	static bool normalState = true;

	if (mRenderState)
	{
		for (auto state : *mRenderState)
		{
			device->SetRenderState(state.first, state.second);
		}
		normalState = false;
	}
	else if(!normalState)
	{
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		device->SetRenderState(D3DRS_ZWRITEENABLE, true);
		device->SetRenderState(D3DRS_STENCILENABLE, false);

		device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		device->SetRenderState(D3DRS_LIGHTING, true);

		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		normalState = true;
	}
	for (DWORD i = 0; i < mNumSubsets; ++i)
	{
		device->SetMaterial(&(*mMtrls)[i]);
		device->SetTexture(0, (*mTextures)[i]);
		mMesh->DrawSubset(i);
	}
}

int C3DModel::Destroy()
{

	// GameRenderer에서 임시 material을 릴리즈함
	mMtrls->clear();
	SAFE_DELETE(mMtrls);

	for (size_t tex = 0; tex < mTextures->size(); ++tex)
	{
		SAFE_RELEASE((*mTextures)[tex]);
	}
	mTextures->clear();
	SAFE_DELETE(mTextures);

	SAFE_RELEASE(mAdjacency);

	SAFE_RELEASE(mMesh);

	SAFE_DELETE(mRenderState);

	return true;
}