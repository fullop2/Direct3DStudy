#include "CTerrain.h"
#include "Vertex.h"

CTerrain::CTerrain(
	LPDIRECT3DDEVICE9& device,
	string heightMapFileName,
	int numVertsPerRow,
	int numVertsPerCol,
	int cellSpacing,
	float heightScale)
	:mDevice(device), mNumVertsPerRow(numVertsPerRow), mNumVertsPerCol(numVertsPerCol), mCellSpacing(cellSpacing), mHeightScale(heightScale)
{
	mNumCellsPerRow = numVertsPerRow - 1;
	mNumCellsPerCol = numVertsPerCol - 1;

	mWidth = mNumCellsPerRow * mCellSpacing;
	mDepth = mNumCellsPerCol * mCellSpacing;

	mNumVertices = mNumVertsPerRow * mNumVertsPerCol;
	mNumTriangles = mNumCellsPerRow * mNumCellsPerCol * 2;

	// load heightmap
	if (!ReadRawFile(heightMapFileName))
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights
	for (int i = 0; i < mHeightMap.size(); i++)
		mHeightMap[i] *= heightScale;

	// compute the vertices
	if (!ComputeVertices())
	{
		::MessageBox(0, "computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	if (!ComputeIndices())
	{
		::MessageBox(0, "computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	LoadTexture("Resource/desert.bmp");
}


CTerrain::~CTerrain()
{
}

bool CTerrain::ReadRawFile(string fileName)
{
	vector<BYTE> in(mNumVertices);
	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if (inFile.fail())
	{
		return false;
	}
	inFile.read(
		(char*)&in[0],
		in.size());
	inFile.close();

	mHeightMap.resize(mNumVertices);
	for (int i = 0; i < in.size(); ++i)
	{
		mHeightMap[i] = in[i];
	}

	return true;
}
int CTerrain::GetHeightMapEntry(int row, int col)
{
	return mHeightMap[row * mNumVertsPerRow + col];
}
void CTerrain::SetHeightMapEntry(int row, int col, int value)
{
	mHeightMap[row * mNumVertsPerRow + col] = value;
}
bool CTerrain::ComputeVertices()
{
	HRESULT hr = 0;

	hr = mDevice->CreateVertexBuffer(
		mNumVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&mVertexBuffer,
		0);

	if (FAILED(hr))
		return false;

	// coordinates to start generating vertices at
	int startX = -mWidth / 2;
	int startZ = mDepth / 2;

	// coordinates to end generating vertices at
	int endX = mWidth / 2;
	int endZ = -mDepth / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	float uCoordIncrementSize = 1.0f / (float)mNumCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)mNumCellsPerCol;

	TerrainVertex* v = 0;
	mVertexBuffer->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for (int z = startZ; z >= endZ; z -= mCellSpacing)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += mCellSpacing)
		{
			// compute the correct index into the vertex buffer and heightmap
			// based on where we are in the nested loop.
			int index = i * mNumVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,
				(float)mHeightMap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}

	mVertexBuffer->Unlock();

	return true;
}
bool CTerrain::ComputeIndices()
{
	HRESULT hr = 0;
	
	hr = mDevice->CreateIndexBuffer(
		mNumTriangles * 3 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&mIndexBuffer,
		0);

	if (FAILED(hr))
	{
		return false;
	}

	DWORD* indices = nullptr;
	mIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	int baseIndex = 0;
	for (int i = 0; i < mNumCellsPerCol; ++i)
	{
		for (int j = 0; j < mNumCellsPerRow; ++j)
		{
			indices[baseIndex]	   =	i *		mNumVertsPerRow + j;
			indices[baseIndex + 1] =	i *		mNumVertsPerRow + j + 1;
			indices[baseIndex + 2] =	(i+1) * mNumVertsPerRow + j;
			indices[baseIndex + 3] =	(i+1) * mNumVertsPerRow + j;
			indices[baseIndex + 4] =	i *		mNumVertsPerRow + j + 1;
			indices[baseIndex + 5] =	(i+1) * mNumVertsPerRow + j + 1;

			baseIndex += 6;
		}
	}
	mIndexBuffer->Unlock();
	return true;
}

bool CTerrain::LoadTexture(string fileName)
{
	HRESULT hr = 0;
	hr = D3DXCreateTextureFromFile(
		mDevice,
		fileName.c_str(),
		&mTexture);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool CTerrain::GenTexture(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;
	int texWidth = mNumCellsPerRow;
	int texHeight = mNumCellsPerCol;

	hr = D3DXCreateTexture(
		mDevice,
		texWidth, texHeight,
		0, 0,
		D3DFMT_X8R8G8B8,
		D3DPOOL_MANAGED,
		&mTexture);

	if (FAILED(hr))
	{
		return false;
	}

	D3DSURFACE_DESC textureDesc;
	mTexture->GetLevelDesc(0, &textureDesc);

	if (textureDesc.Format != D3DFMT_X8R8G8B8)
	{
		return false;
	}

	D3DLOCKED_RECT lockedRect;
	mTexture->LockRect(0, &lockedRect, 0, 0);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texHeight; ++i)
	{
		for (int j = 0; j < texWidth; ++j)
		{
			D3DXCOLOR c;

			float height = (float)GetHeightMapEntry(i, j) / mHeightScale;

			if ((height) < 42.5f) 		 c = BEACH_SAND;
			else if ((height) < 127.5f) c = PUREGREEN;
			else if ((height) < 170.0f) c = DARK_YELLOW_GREEN;
			else if ((height) < 212.5f) c = DARKBROWN;
			else	                     c = WHITE;

			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		} 
	}

	mTexture->UnlockRect(0);

	
	
	if(!LightTerrain(directionToLight))
	{
		MessageBox(0,"lightTerrain() - FAILED",0,0);
		return false;
	}
	

	hr = D3DXFilterTexture(
		mTexture,
		0,// default palatte
		0,// src level 
		D3DX_DEFAULT);

	if (FAILED(hr))
	{
		MessageBox(0, "D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}

bool CTerrain::LightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc;
	mTexture->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code that fills the
	// texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	mTexture->LockRect(
		0,          // lock top surface level in mipmap chain
		&lockedRect,// pointer to receive locked data
		0,          // lock entire texture image
		0);         // no lock flags specified

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (size_t i = 0; i < textureDesc.Height; i++)
	{
		for (size_t j = 0; j < textureDesc.Width; j++)
		{
			// index into texture, note we use the pitch and divide by 
			// four since the pitch is given in bytes and there are 
			// 4 bytes per DWORD.
			size_t index = i * lockedRect.Pitch / 4 + j;

			// get current color of quad
			D3DXCOLOR c(imageData[index]);

			// shade current quad
			//c *= computeShade(i, j, directionToLight);;

			// save shaded color
			//imageData[index] = (D3DCOLOR)c;

			float s = ComputeShade(i, j, directionToLight);
			imageData[index] = D3DXCOLOR(s, s, s, 1.0f);
		}
	}

	mTexture->UnlockRect(0);

	return true;
}


float CTerrain::ComputeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	float heightA = static_cast<float>(GetHeightMapEntry(cellRow, cellCol));
	float heightB = static_cast<float>(GetHeightMapEntry(cellRow, cellCol + 1));
	float heightC = static_cast<float>(GetHeightMapEntry(cellRow + 1, cellCol));

	D3DXVECTOR3 u{ (float)mCellSpacing, heightB - heightA, 0.0f };
	D3DXVECTOR3 v{ 0.0f,heightC - heightA, -(float)mCellSpacing };

	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, directionToLight);
	if (cosine < 0.0f)
		cosine = 0.0f;
	return cosine;
}

void CTerrain::Draw(LPDIRECT3DDEVICE9& device)
{
	HRESULT hr = 0;

	if (device)
	{
		device->SetStreamSource(0, mVertexBuffer, 0, sizeof(TerrainVertex));
		device->SetFVF(TerrainVertex::FVF);
		device->SetIndices(mIndexBuffer);

		device->SetTexture(0, mTexture);

		// turn off lighting since we're lighting it ourselves
		device->SetRenderState(D3DRS_LIGHTING, false);

		hr = device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			mNumVertices,
			0,
			mNumTriangles);

		device->SetRenderState(D3DRS_LIGHTING, true);
		/*
		if (drawTris)
		{
			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			hr = _device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				_numVertices,
				0,
				_numTriangles);

			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		*/
	}
}