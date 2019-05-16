#pragma once
#include "ObjectBuffer.h"
#include <fstream>

class CTerrain
{
public:
	bool ReadRawFile(string fileName);
	int GetHeightMapEntry(int row, int col);
	void SetHeightMapEntry(int row, int col, int value);
	bool ComputeVertices();
	bool ComputeIndices();
	bool LoadTexture(string fileName);
	bool GenTexture(D3DXVECTOR3* directionToLight);
	bool LightTerrain(D3DXVECTOR3* directionToLight);
	float ComputeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);

	void Draw(LPDIRECT3DDEVICE9& device);

public:
	CTerrain(
		LPDIRECT3DDEVICE9& device,
		string heightMapFileName,
		int numVertsPerRow,
		int numVertsPerCol,
		int cellSpacing,
		float heightScale);
	~CTerrain();


private:
	LPDIRECT3DDEVICE9& mDevice;
	IDirect3DVertexBuffer9* mVertexBuffer;
	IDirect3DIndexBuffer9* mIndexBuffer;
	vector<int> mHeightMap;
	IDirect3DTexture9* mTexture;

	D3DXVECTOR3 mPosition;

	int mNumVertsPerRow;
	int mNumVertsPerCol;
	int mCellSpacing;

	int mNumCellsPerRow;
	int mNumCellsPerCol;
	int mWidth;
	int mDepth;
	int mNumVertices;
	int mNumTriangles;

	float mHeightScale;
};

