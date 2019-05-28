#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	SetObject2DLayerSize(10);
}

ObjectManager::~ObjectManager()
{
	Destroy();
}

void ObjectManager::Destroy()
{
	size_t layerSize = mObjects2D.size();
	for (int layer = 0; layer < layerSize; ++layer)
	{
		for (Object2D* object : mObjects2D[layer])
		{
			Object2D* delOb = object;
			delOb->Destroy();
			SAFE_DELETE(delOb);
		}
		mObjects2D[layer].clear();
	}
	mObjects2D.clear();

}

int ObjectManager::Update(float deltaTime)
{
	objects.Update(deltaTime);
	UpdateObject2D(deltaTime);
	//object3D.Update();
	//objectBuffer.Update();
	//text.Update();
	//objectStencil.Update();

	return true;
}

int ObjectManager::UpdateObject2D(float deltaTime)
{
	size_t layerSize = mObjects2D.size();
	for (size_t layer = 0; layer < layerSize; ++layer)
	{
		for (auto object = mObjects2D[layer].begin(); object != mObjects2D[layer].end();)
		{
			if ((*object)->GetAvailable() && !(*object)->Update(deltaTime))
			{
				Object2D* destroyObject = *object;
				destroyObject->Destroy();
				object = mObjects2D[layer].erase(object);
				delete destroyObject;
			}
			else
			{
				++object;
			}
		}
	}
	return true;
}

void ObjectManager::Draw(IDirect3DDevice9* device)
{

	////////////////////////////////////////////////
	// using buffer to draw 3d object

	device->SetRenderState(D3DRS_LIGHTING, true);
	const vector<Object3D*>& Objects = objects.Get();
	for (auto object : Objects)
	{
		if (object->GetAvailable())
		{
			device->SetTransform(D3DTS_WORLD, &UpdateTransform(object));
			object->Draw(device);
		}
	}

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void ObjectManager::Draw2D(ID3DXSprite* sprite)
{
	int layerSize = GetObject2DLayerSize();
	for (int depth = layerSize - 1; depth >= 0; --depth)
	{
		const vector<Object2D*>& layer = GetObjects2DLayer(depth);
		for (Object2D* object : layer)
		{
			if (object->GetAvailable())
			{
				sprite->SetTransform(&UpdateTransform(object));
				object->Draw(sprite);
			}
		}
	}
}
D3DXMATRIX ObjectManager::UpdateTransform(Object* object)
{
	D3DXMATRIX translation, rotation, scaling;
	D3DXMatrixIdentity(&translation);
	scaling = rotation = translation;

	// scaling
	D3DXVECTOR3 scale = object->GetScale();
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);

	// rotation
	D3DXVECTOR3 rotate = object->GetRotation();

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);

	D3DXMatrixRotationX(&temp, D3DXToRadian(rotate.x));
	rotation *= temp;
	D3DXMatrixRotationY(&temp, D3DXToRadian(rotate.y));
	rotation *= temp;
	D3DXMatrixRotationZ(&temp, D3DXToRadian(rotate.z));
	rotation *= temp;

	// translation

	D3DXVECTOR3 translate = object->GetPosition();
	D3DXMatrixTranslation(&translation, translate.x, translate.y, translate.z);

	scaling *= rotation;
	scaling *= translation;
	return scaling;
}