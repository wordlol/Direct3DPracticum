#pragma once
#include "StartWin.h"
#include "Graphics.h"
#include <memory>
#include "Timers.h"
#include "math.h"
#include <optional>

class Window
{
private:
	class WinClass
	{
	public:
		static const wchar_t* GetName() 
		{ //����� ����� �������� ��� ������
		return wndClassName;
		};
		static HINSTANCE GetInstance()
		{ //����� ����� �������� ������ �� ���������
		return wndClass.hInst;
		}; 
	private:
		WinClass(); //����������� ��� ���������� ������� WNDCLASSEX � �����������
		~WinClass() 
		{ //���������� ��� �������
		UnregisterClass(wndClassName, GetInstance()); 
		}; 

		WinClass(const WinClass&) = delete;			    //������ ����������� �����, �� ����� �������� �����������, ��� ���������� ����� ������ �� ����� ���� �����������
		WinClass& operator=(const WinClass&) = delete;  //���� ������� ��������� ���������� ����� ��� ������

		static constexpr const wchar_t* wndClassName = L"Direct3DPracticum"; //��� ����� � ��������� ����� �� ��� ��� ������ ������ "����������� ����������.exe"
		static WinClass wndClass; //����������� ��������� ������
		HINSTANCE hInst; // ���� �� ���������� WNDCLASSEX
	};

//��� ������ Window
public:
	Window(int width, int height, const wchar_t* name)
	{
		RECT wr; //��������� � ������� ��������� �������
		wr.left = 0;//��������� x-��������� �������� ������ ���� ��������������
		wr.right = width + wr.left;//��������� x-��������� ������� ������� ���� ��������������
		wr.top = 0;//��������� y-��������� �������� ������ ���� ��������������
		wr.bottom = height + wr.top;//��������� y-��������� ������� ������� ���� ��������������
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE); //������������ ����������� ������ �������� ��������������, ������ �� ��������� ������� ������-���������� ����
		//�������� ����
		hWnd = CreateWindow( //���� ������� ��������� �������, ������������ �������� �������� ������������ � ����� ����
			WinClass::GetName(), //��������� ��� ������ ����. ��� ������ ����� ���� ����� ������, ������������������ � ������� RegisterClass
			name, // ��� ����. ���� ����� ���� ������ ������ ���������, � ������ ��������� ������������ �������� ����, �� ������� ��������� lpWindowName
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //����� ������������ ���� //����� ����� ���������� ����� https://learn.microsoft.com/ru-ru/windows/win32/winmsg/window-styles
			CW_USEDEFAULT,// ��������� �������������� ������� ����, ���� ��� �� CW_USEDEFAULT �� �� � ShowWindow(hWnd, ...) ��������� nCmdShow
			CW_USEDEFAULT,// ��������� ������������ ������� ����
			wr.right - wr.left, // ������ ���� � �������� ����������, ���� �������� nWidth ��� nHeight ����� �������� CW_USEDEFAULT
			wr.bottom - wr.top, // ������ ���� � �������� ���������� 
			nullptr, //���������� ���� ������������� ��� ��������� ������������ ����
			nullptr, //���������� ���� ��� ������ ������������� ��������� ���� � ����������� �� ����� ����
			WinClass::GetInstance(), //���������� ���������� ������, ���������� � �����
			this //��������� �� ��������, ������������ � ���� ����� ��������� CREATESTRUCT CREATESTRUCT (������� lpCreateParams), �� ������� ��������� lParam ����� ��������� WM_CREATE
		);
		ShowWindow(hWnd, SW_SHOW);//����� ����
		pGfx = std::make_unique<Graphics>(hWnd);
	};
	~Window() 
	{ 
		DestroyWindow(hWnd); //������� ��� �������� ����
	};

	Window(const Window&) = delete;			   //������ ����������� �����, �� ����� �������� �����������, ��� ���������� ����� ������ �� ����� ���� �����������
	Window& operator=(const Window&) = delete; //���� ������� ��������� ���������� ����� ��� ������
	
	//����� ����� �������
	Graphics& Gfx()
	{
		return *pGfx;
	};
	static std::optional<int> ProcessMessages() 
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return {};
	};
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //������� ��������� ���������
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //������� ����������
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);					   //������� ��� ��������� ��������� ���������
private:
	int width; //������ ����
	int height; //������ ����
	HWND hWnd; //��������� ���������� ����
	std::unique_ptr<Graphics>pGfx; //d3d11 �������
};
Window::WinClass Window::WinClass::wndClass; //���������� ����������� ������� ����������

//���������� ������� � ������� WinMain 
Window::WinClass::WinClass():hInst(GetModuleHandle(nullptr)) // GetModuleHandle(LPCSTR lpModuleName) ��������� ���������� ������ ��� ���������� ������
{
	WNDCLASSEX wc = { 0 }; // ��������� �������� �������� � ����
	wc.cbSize = sizeof(wc);// ������ ���� ��������� � ������
	wc.style = CS_OWNDC;// ���� ������� ����� ���� ����� ���������� ������ �������
	wc.lpfnWndProc = HandleMsgSetup;// ��������� �� ��������� ����
	wc.cbClsExtra = 0;// ���������� �������������� ������, ���������� ����� ��������� ������ ����
	wc.cbWndExtra = 0;// ���������� �������������� ������, ���������� ����� ���������� ����
	wc.hInstance = GetInstance();// ���������� ����������, ����������� ��������� ���� ��� ������
	wc.hIcon = static_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));// ���������� ������ ������. ���� ������� ������ ���� ������������ ������� ������
	wc.hCursor = nullptr;// ���������� ������� ������. ���� ������� ������ ���� ������������ ������� �������
	wc.hbrBackground = nullptr;// ���������� ������� ����� ������. ���� ������� ����� ���� ������������ �����, ������������ ��� ��������� ����
	wc.lpszMenuName = nullptr;// ��������� �� ������ ��������, ��������� ��� ������� ���� ������, ��� ��� ��� ������������ � ����� �������
	wc.lpszClassName = GetName();// �������� �������, �� ��������� ��� ������ ����. ��� ������ ����� ���� ����� ������, ������������������ � RegisterClass
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0)); // ���������� ���������� ������, ���������� � ������� ����
	RegisterClassEx(&wc);// ������������ ����� ���� ��� ������������ ������������� � ������� ������� CreateWindow ��������� ��� �������� ATOM
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) // ��������� ����� ��������� ���� ��-���� ����� WM_CREATE
	{ 
		// reinterpret_cast <type - id> (expression)
		// ��������� ��������������� ����� ��������� � ��������� ������ ������� ����. 
		// ����� ��������� ��������������� ����� ������������� ��� � ����� ��� ��������� � ��������

		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam); // ���������� ��������� �������������, ������������ � ��������� ���� ����������.
		// static_cast ����������� ��������� � ��� �������������� ����, ����������� ������ �� �����, �������������� � ���������
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams); // ��������� ��� ��������� � ����� pWnd 
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));//�������� ������� ���������� ����. ������� ����� ������ �������� �� ���������� ��������� � �������������� ���� ������
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));// �������� �������� � ����������� ��� � ������������ ����������� �� ���������
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);// ���������� ��� ��������� � ����������� ��� ��������
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);// ������ ������� ���������
};

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));//���������� ������ window � ��������� ���������� � �����������
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);//���������� ��� ������� ��������� � ���� ���������
};

// Windows ����� ������ ����� ������� window-procedure. ��� ������� ����������, WndProc 
// � ���� ������� �� ������ ��� ��� ��������� ���������
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) //��� ���������
	{
	case WM_CLOSE: //��� ������������� ���������
		PostQuitMessage(0); //�������� ��������� �� �������� ���� � ������� ��������� � ����� 0
		return 0;
	
		//��� ����� ������ ���������, � ������������ �� �������� ����� ����� 1000+ ���������
		

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);//��� ������� ����������� ��������� ������� ���������. ���������� � ���� �� �����������, ��� � ��������� ����. 
													//��� �� ���� �������  CallWindowProc 	�������� �������� � ��������� � ��������� ��������� ����. 
														//WindowProc ������������ ����������� �������, ������� ������������ ���������, ������������ � ����.
		break;
	}
};