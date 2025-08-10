#pragma once
#include "StartWin.h"
#include "Graphics.h"
#include <memory> /// позволяет выделять и освобождать объекты может понадобиться для создания объектов до их инициализации как указатель на уникальный объект
#include "Timers.h"
#include "math.h"
#include <optional> /// нужен для опредления оциональных данных или обьявлений которые могут быть а могут и не быть но это не является ошибкой

class Window
{
private:
	class WinClass
	{
	public:
		static const wchar_t* GetName() 
		{
		return wndClassName;
		};
		static HINSTANCE GetInstance()
		{
		return wndClass.hInst;
		}; 
	private:
		WinClass(); 
		~WinClass() 
		{ 
		UnregisterClass(wndClassName, GetInstance()); 
		}; 

		WinClass(const WinClass&) = delete;			    
		WinClass& operator=(const WinClass&) = delete;  

		static constexpr const wchar_t* wndClassName = L"Direct3DPracticum"; 
		static WinClass wndClass; 
		HINSTANCE hInst; 
	};


public:
	Window(int width, int height, const wchar_t* name)
	{
		RECT wr;
		wr.left = 0;
		wr.right = width + wr.left;
		wr.top = 0;
		wr.bottom = height + wr.top;
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE); 
		hWnd = CreateWindow( 
			WinClass::GetName(),
			name, 
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left, 
			wr.bottom - wr.top, 
			nullptr, 
			nullptr, 
			WinClass::GetInstance(), 
			this 
		);
		ShowWindow(hWnd, SW_SHOW);
		pGfx = std::make_unique<Graphics>(hWnd);///Создает и возвращает unique_ptr, указывающий на выделенный объект, созданный из нуля или нескольких аргументов.
	};
	~Window() 
	{ 
		DestroyWindow(hWnd); //функция для удаления окна
	};

	Window(const Window&) = delete;			  
	Window& operator=(const Window&) = delete; 
	

	Graphics& Gfx()
	{
		return *pGfx;
	};
	static std::optional<int> ProcessMessages() /// в данном случае как раз могут использоваться различные выходные данные от -1 до 0 и >0 если такой будет код запроса
	{   //// этот обработчик сообщений нужнен чтобы обрабатываться сообщения без остановки приложения если оно не получает новых сообщений
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) /// обрабатывает сообщения даже если их нет
		{
			if (msg.message == WM_QUIT)/// сообщение о выходе
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return {}; /// вернет значение по умолчанию
	};
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);					   
private:
	int width; 
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics>pGfx; ///Хранит указатель на собственный объект. Указатель не принадлежит никаким другим unique_ptr. unique_ptr удаляется при удалении владельца
};
Window::WinClass Window::WinClass::wndClass; 

Window::WinClass::WinClass():hInst(GetModuleHandle(nullptr)) 
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{ 
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
};

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
};

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_CLOSE: 
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
};