#pragma once
#include "TemplatedObjectManager.h"
#include "Object.h"
#include "Object2D.h"
#include "Object3D.h"
#include "CTerrain.h"

class ObjectManager
{
public:
	// ctor, dtor
	ObjectManager();
	~ObjectManager();

	// Getter, Setter //

	// Object2D
	const vector<Object2D*>& GetObjects2DLayer(int layer)
	{
		return mObjects2D[layer];
	}
	void AddObject2D(Object2D* object, int layer = 0)
	{
		mObjects2D[layer].push_back(object);
	}
	// 2D Layer Size
	const size_t GetObject2DLayerSize()
	{
		return mObjects2D.size();
	}
	void SetObject2DLayerSize(int layerSize)
	{
		mObjects2D.resize(layerSize);
	}

	void Add(CTerrain* pObject) { terrain.Add(pObject); }
	void Add(Object3D* pObject) { objects.Add(pObject); }
	void Add(Object* pObject){ baseComponents.Add(pObject); }
	void Destroy();
	int Update();
	int UpdateObject2D();
	void Draw(IDirect3DDevice9* device);
	void Draw2D(ID3DXSprite* sprite);


	TemplatedObjectManager<CTerrain> terrain;
	TemplatedObjectManager<Object3D> objects;
	TemplatedObjectManager<Object> baseComponents;
	
private:
	// 나열자 둔갑술을 위한 enum
	// 미사용
	/*
	enum _layerSize
	{
		layersize = 20
	}layerSize;

	//vector<GameObject2D*>				objects[layersize];
	*/

	vector < vector<Object2D*> >	mObjects2D;


	D3DXMATRIX UpdateTransform(Object* object);
};

namespace layer
{
	enum Layer
	{
		Button,
		UI,
		Player,
		Monster,
		Item
	};
}