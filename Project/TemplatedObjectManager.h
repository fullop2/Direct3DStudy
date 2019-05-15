#pragma once
#include "stdafx.h"

// 여러 오브젝트가 있어서 템플릿화~

template <typename T>
class TemplatedObjectManager
{
public:
	TemplatedObjectManager() {};
	~TemplatedObjectManager()
	{
		Destroy();
	};

	const vector<T*>& Get()
	{
		return mObjectList;
	}

	void Add(T* object)
	{
		mObjectList.push_back(object);
	}

	int Update() 
	{
		for (auto object = mObjectList.begin(); object != mObjectList.end();)
		{
			if ((*object)->GetAvailable() && !(*object)->Update())
			{
				T* destroyObject = *object;
				object = mObjectList.erase(object);
				delete destroyObject;
			}
			else
			{
				++object;
			}
		}
		return true;
	}
	void Destroy()
	{
		for (T* object : mObjectList)
		{
			T* delOb = object;
			delOb->Destroy();
			SAFE_DELETE(delOb);
		}
		mObjectList.clear();
	}

private:
	vector <T*>	mObjectList;
};

