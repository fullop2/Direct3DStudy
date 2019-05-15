

#include "Object3D.h"
#include "Window.h"

//// vector

Object3D::Object3D()
	:Object()
{
	mModel = nullptr;
}

Object3D::~Object3D()
{
	delete mModel;
}

bool Object3D::Init(C3DModel* model)
{
	if (model)
	{
		mModel = model;
	}
	else
	{
		mModel = new C3DModel();
	}
	return true;
}

bool Object3D::Init(LPCSTR name)
{
	mModel = new C3DModel(name);
	return true;
}

int Object3D::Update()
{
	/*
	if (mModel)
	{
		float& dif = mModel->mMtrls[0].Diffuse.a;
		if (GetKeyDown('A') && dif > 0.0f)
			dif -= 0.01f;
		if (GetKeyDown('S') && dif < 1.0f)
			dif += 0.01f;
	}
			*/
	 return true;
}
void Object3D::Draw(IDirect3DDevice9* device)
{
	mModel->Draw(device);
}


int Object3D::Destroy()
{
	return true;
}