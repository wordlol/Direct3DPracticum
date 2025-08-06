#pragma once
#include "StartWin.h"

class Window
{
private:
	class WinClass
	{
	public:
		//можно будет получить им€ класса
		static const wchar_t* GetName() 
	{
		return wndClassName;
	};
		//можно будет получить ссылку на экземпл€р
		static HINSTANCE GetInstance()
	{
		return wndClass.hInst;
	}; 
	private:
		//конструктор дл€ регистрации
		WinClass(); 
		//диструктор дл€ отмены регистрации
		~WinClass() 
		{ 
		UnregisterClass(wndClassName, GetInstance()); 
		}; 
		WinClass(const WinClass&) = delete;
		WinClass& operator=(const WinClass&) = delete;
		static constexpr const wchar_t* wndClassName = L"Direct3DPracticum";
		static WinClass wndClass; //статический экземпл€р класса
		HINSTANCE hInst;
	};
public:
	//создание окна
	Window(int width, int height, const wchar_t* name)
	{
		RECT wr;
		wr.left = 600;
		wr.right = width + wr.left;
		wr.top = 600;
		wr.bottom = height + wr.top;
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE); //функци€ настройки окна область где будет работать пользователь
		hWnd = CreateWindow(
			WinClass::GetName(), name,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT,
			wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr,
			WinClass::GetInstance(),
			this //передает указатель экзепл€ра на себ€
		);
	};
	//удаление окна
	~Window() 
	{
		DestroyWindow(hWnd);
	};
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	//функци€ обработки сообщений
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//функци€ обработчик
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//функци€ 
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	};

	int width;
	int height;
	HWND hWnd;
};
Window::WinClass Window::WinClass::wndClass; //объе€вл€ем статическую функцию экземпл€ра
Window::WinClass::WinClass():hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) //проверка на то создалась ли неклиенска€ область окна
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
};

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
};