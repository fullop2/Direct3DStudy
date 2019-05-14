#include "SceneManager.h"
#include "Scene.h"
#include "stdafx.h"

SceneManager::SceneManager()
	:mScene(nullptr), mSceneState(true)
{
}


SceneManager::~SceneManager()
{
	delete mScene;
}

bool SceneManager::LoadScene(Scene* scene)
{
	if (scene->Init())
	{
		SAFE_DELETE(mScene);
		mScene = scene;
		return true;
	}
	else
	{
		return false;
	}
}


int SceneManager::Loop()
{
	mScene->Update();
	mScene->Draw();
	//mScene->DrawStencil();
	return mSceneState;
}