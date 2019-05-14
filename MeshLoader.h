#pragma once

#include "stdafx.h"

class C3DModel;

// ¹Ì±¸Çö
class MeshLoader
{
public:
	HRESULT Create(LPCSTR dir, C3DModel* model);

	MeshLoader(LPDIRECT3DDEVICE9 device);
	~MeshLoader();

private:
	LPDIRECT3DDEVICE9 mDevice;
};

