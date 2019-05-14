#pragma once
#include "stdafx.h"

class C3DModel;
class CTexture;

// GameRenderer.cpp : 게임 렌더러 
// Direct3D의 장치를 생성하고 삭제하는 역할을 수행한다
// 이 클래스를 통해 생성된 장치(device)에다가 드로잉을 수행한다

class Renderer
{
public:
	Renderer(HWND hWnd);
	~Renderer();

	const LPDIRECT3DDEVICE9&	GetDevice() { return mDevice; };
	const LPD3DXSPRITE&			GetSprite() { return mSprite; };
	void				CleanD3D();
	LPDIRECT3DTEXTURE9	LoadTexture(LPCSTR name, D3DXIMAGE_INFO* srcInfo);
	void				Load2DTexture(LPCSTR name, CTexture** pTexture);
	void				LoadXObjects(LPCSTR name, C3DModel** ppModel);

private:
	LPDIRECT3D9			mD3D;
	LPDIRECT3DDEVICE9	mDevice;
	LPD3DXSPRITE		mSprite;
};