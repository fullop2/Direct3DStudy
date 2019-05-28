#pragma once

#include "Object.h"
#include "C3DModel.h"

//
// 3d 메시를 이용해 draw하는 객체
// 

class Object3D : public Object
{
public:
	Object3D()
		:Object()
	{
		mModel = nullptr;
	}
	~Object3D()
	{
		delete mModel;
	}

	bool Init(C3DModel* model = nullptr)
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
	bool Init(LPCSTR name)
	{
		mModel = new C3DModel(name);
		return true;
	}
	virtual void Draw(IDirect3DDevice9* device)
	{
		mModel->Draw(device);
	}

	virtual int Update(float deltaTime) override
	{
		return true;
	}
	virtual int Destroy() override
	{
		return true;
	}
	const C3DModel* GetC3DModel()
	{
		return mModel;
	}

protected:
	C3DModel* mModel;
};