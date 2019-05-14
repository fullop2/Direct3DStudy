#include "Renderer.h"
#include "Window.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"

bool keyDown[256];
bool bMouseDown;
struct mousePosition
{
	int x;
	int y;
} MousePosition;

Window::Window()
{
	WNDCLASS WndClass = { 0, WndProc, 0, 0, GetModuleHandle(0), 0, 0, 0, 0, "DirectX9" };
	RegisterClass(&WndClass);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	mhWnd = CreateWindow("DirectX9", "FirstGame", WS_OVERLAPPEDWINDOW, x, y, width, height, 0, 0, WndClass.hInstance, 0);
	ShowWindow(mhWnd, SW_SHOW);
	UpdateWindow(mhWnd);
	
	Timer::Get().Init();
}


Window::~Window()
{
	
}

bool Window::ChangeScene(Scene* scene)
{
	return SceneManager::Get()->LoadScene(scene);
}

void Window::Loop(Renderer* renderer)
{
	MSG msg;

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, 0, 0, 0))
				break;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Timer::Get().Frame();

			if (SceneManager::Get()->Loop() == 0)
			{
				break;
			}
		}
	}
	renderer->CleanD3D();
}

const bool GetKeyDown(int keyCode)
{
	return keyDown[keyCode];
}

LRESULT CALLBACK Window::WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		
		MousePosition.x = LOWORD(lParam);
		MousePosition.y = HIWORD(lParam);
		bMouseDown = true;
		break;
	case WM_LBUTTONUP:
		bMouseDown = false;
		break;
	case WM_KEYDOWN:
		keyDown[wParam] = true;
		break;
	case WM_KEYUP:
		keyDown[wParam] = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}