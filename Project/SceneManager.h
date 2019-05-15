#pragma once

class Scene;

class SceneManager
{
public:
	bool LoadScene(Scene* scene);
	static SceneManager* Get()
	{
		static SceneManager ins;
		return &ins;
	}
	int Loop(float timeDelta);

	void EndScene() { mSceneState = false; };
private:
	SceneManager();
	~SceneManager();

	Scene* mScene;

	bool mSceneState;
};

