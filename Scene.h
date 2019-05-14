#pragma once
#include "stdafx.h"
#include "ObjectManager.h"

class Object;
class FlexCamera;
class Camera;
class Renderer;
class Timer;


class Scene
{
public:
	Scene(Renderer* renderer);

	virtual ~Scene()
	{
	}

	virtual bool Init() = 0;

	void Draw();
	//void DrawStencil();
	void Destroy();
	void Update();

protected:
	Renderer*		mRenderer;
	D3DXMATRIX			mProjection;

	IDirect3DDevice9 *	mDevice;
	ID3DXSprite *		mSprite;
	Camera*				mCamera;
	Timer*				mTimer;

	D3DXCOLOR			mSkyColor;
	ObjectManager  mObjectManager;
};