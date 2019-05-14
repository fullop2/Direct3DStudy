#pragma once
#include "stdafx.h"
#include "Vertex.h"
#include <list>

struct BoundingBox
{
	D3DXVECTOR3 p1, p2;
};

class ParticleSystem
{
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	virtual bool init(LPDIRECT3DDEVICE9 device, char* texFileName);
	virtual void reset();
	virtual void resetParticle(Attribute* attribute) = 0;
	virtual void addParticle();
	virtual void update(float timeDelta) = 0;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	bool isEmpty();
	bool isDead();
	
protected:
	virtual void removeDeadParticles();

protected:
	IDirect3DDevice9* mDevice;
	D3DXVECTOR3 mOrigin;
	BoundingBox mBoundingBox;
	float mEmitRate;
	float mSize;
	IDirect3DTexture9* mTex;
	IDirect3DVertexBuffer9* mVB;
	std::list<Attribute> mParticles;
	int maxParticles;

	DWORD mVBSize;
	DWORD mVBOffset;
	DWORD mVBBatchSize;
};

