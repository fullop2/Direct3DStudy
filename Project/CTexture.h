#pragma once
#include "stdafx.h"

class Renderer;
class Object3D;

class CTexture
{
public:
	CTexture()
		:mTexture(nullptr),mWidth(0),mHeight(0)
	{}
	CTexture(IDirect3DTexture9* texture, int height, int width)
		:mTexture(texture), mHeight(height), mWidth(width)
	{}
	~CTexture();

	void GetTexture(LPDIRECT3DTEXTURE9 * ppTexture)
	{
		*ppTexture = mTexture;
	};
	const int GetWidth() { return mWidth; }
	const int GetHeight() { return mHeight; }


private:
	IDirect3DTexture9 * mTexture;
	INT mWidth;
	INT mHeight;
};
