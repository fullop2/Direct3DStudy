#pragma once

#include "Object.h"
#include "C3DModel.h"

//
// 3d �޽ø� �̿��� draw�ϴ� ��ü
// 

class Object3D : public Object
{
public:
	Object3D();
	~Object3D();

	bool Init(C3DModel* model = nullptr);
	bool Init(LPCSTR name);
	void Draw(IDirect3DDevice9* device);

	virtual int Destroy() override;
	virtual int Update() override;


	const C3DModel* GetC3DModel()
	{
		return mModel;
	}

protected:
	C3DModel* mModel;
};