#include "Window.h"
#include "Renderer.h"
#include "Stage_Main.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// 누수 체크
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// 누수 포인트를 체크하여 중단점으로 반환
	// _crtBreakAlloc = 180;
	Window window;
	Renderer renderer(window.GetWindowHandler());
	Stage_Main* stage = new Stage_Main(&renderer);
	if(window.ChangeScene(stage))
		window.Loop(&renderer);

	return 0;
}