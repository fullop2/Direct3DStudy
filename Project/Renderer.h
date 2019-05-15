#pragma once
#include "stdafx.h"

class C3DModel;
class CTexture;

// GameRenderer.cpp : ���� ������ 
// Direct3D�� ��ġ�� �����ϰ� �����ϴ� ������ �����Ѵ�
// �� Ŭ������ ���� ������ ��ġ(device)���ٰ� ������� �����Ѵ�

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