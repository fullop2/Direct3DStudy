#pragma once

// windows sdk 17763 version

#include <Windows.h>

const bool GetKeyDown(int keyCode);

class Renderer;
class Scene;
class Timer;

class Window
{
public:
	Window();
	~Window();

	void Loop(Renderer*);
	bool ChangeScene(Scene* scene);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	const HWND GetWindowHandler() { return mhWnd; }

private:
	HWND		mhWnd;
};

