#pragma once

#include "stdafx.h"
#include "MeshLoaderOBJ/Source/OBJ_Loader.h"
class C3DModel;

// ¹Ì±¸Çö
class MeshLoader
{
public:
	MeshLoader(LPDIRECT3DDEVICE9 device);
	~MeshLoader();

	void get3DObject(string fileName, ID3DXBaseMesh** ppMesh, MtrlVec** mtrlVec, TexVec** texVec);
private:
	LPDIRECT3DDEVICE9 mDevice;
	objl::Loader loader;


};

