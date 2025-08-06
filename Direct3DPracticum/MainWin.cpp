#include "WindowsFrameWork.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	Window wnd(600, 600, L"Hello world");

	
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}
	
	return msg.wParam;
};