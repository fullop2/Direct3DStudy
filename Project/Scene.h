#pragma once
#include "stdafx.h"
#include "ObjectManager.h"

class Camera;
class Renderer;
class ParticleSystem;
class CText;
class CTerrain;
class Light;

class Scene
{
public:
	Scene(Renderer* renderer);

	virtual ~Scene();

	virtual bool Init() = 0;

	void Draw();
	//void DrawStencil();
	void Destroy();
	void Update(float timeDelta);

protected:
	Renderer*			mRenderer;
	D3DXMATRIX			mProjection;

	IDirect3DDevice9 *	mDevice;
	ID3DXSprite *		mSprite;

	D3DXCOLOR			mSkyColor;

	Camera*				mCamera;
	CTerrain* mTerrain;
	vector<ParticleSystem*>		mParticleSystem;
	vector<CText*>			mText;
	vector<Light*>		mLight;

	ObjectManager  mObjectManager;
};