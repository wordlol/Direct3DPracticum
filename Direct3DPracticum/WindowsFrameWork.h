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
		{ //можно будет получить имя класса
		return wndClassName;
		};
		static HINSTANCE GetInstance()
		{ //можно будет получить ссылку на экземпляр
		return wndClass.hInst;
		}; 
	private:
		WinClass(); //конструктор для добавления функций WNDCLASSEX и регистрации
		~WinClass() 
		{ //диструктор для отписки
		UnregisterClass(wndClassName, GetInstance()); 
		}; 

		WinClass(const WinClass&) = delete;			    //Удалив конструктор копий, вы прямо сообщите компилятору, что экземпляры этого класса не могут быть скопированы
		WinClass& operator=(const WinClass&) = delete;  //Явно удаляет оператора назначения копий для класса

		static constexpr const wchar_t* wndClassName = L"Direct3DPracticum"; //имя файла в диспечере задач ну или имя нашего класса "запускаемое приложение.exe"
		static WinClass wndClass; //статический экземпляр класса
		HINSTANCE hInst; // сюда мы перемещаем WNDCLASSEX
	};

//для класса Window
public:
	Window(int width, int height, const wchar_t* name)
	{
		RECT wr; //структура с данными квадарата области
		wr.left = 0;//Указывает x-координат верхнего левого угла прямоугольника
		wr.right = width + wr.left;//Указывает x-координат нижнего правого угла прямоугольника
		wr.top = 0;//Указывает y-координат верхнего левого угла прямоугольника
		wr.bottom = height + wr.top;//Указывает y-координат нижнего правого угла прямоугольника
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE); //Рассчитывает необходимый размер оконного прямоугольника, исходя из желаемого размера клиент-прямящийся угол
		//создание окна
		hWnd = CreateWindow( //Если функция выполнена успешно, возвращаемое значение является дескриптором в новом окне
			WinClass::GetName(), //указывает имя класса окна. Имя класса может быть любым именем, зарегистрированным в функции RegisterClass
			name, // Имя окна. Если стиль окна задает строку заголовка, в строке заголовка отображается название окна, на которое указывает lpWindowName
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Стиль создаваемого окна //стили можно посмотреть здесь https://learn.microsoft.com/ru-ru/windows/win32/winmsg/window-styles
			CW_USEDEFAULT,// Начальная горизонтальная позиция окна, если тут не CW_USEDEFAULT то мы в ShowWindow(hWnd, ...) указываем nCmdShow
			CW_USEDEFAULT,// Начальная вертикальная позиция окна
			wr.right - wr.left, // Ширина окна в единицах устройства, Если параметр nWidth или nHeight имеет значение CW_USEDEFAULT
			wr.bottom - wr.top, // Высота окна в единицах устройства 
			nullptr, //Дескриптор окна родительского или владельца создаваемого окна
			nullptr, //Дескриптор меню или задает идентификатор дочернего окна в зависимости от стиля окна
			WinClass::GetInstance(), //Дескриптор экземпляра модуля, связанного с окном
			this //Указатель на значение, передаваемое в окно через структуру CREATESTRUCT CREATESTRUCT (элемент lpCreateParams), на который указывает lParam парам сообщения WM_CREATE
		);
		ShowWindow(hWnd, SW_SHOW);//показ окна
		pGfx = std::make_unique<Graphics>(hWnd);
	};
	~Window() 
	{ 
		DestroyWindow(hWnd); //функция для удаления окна
	};

	Window(const Window&) = delete;			   //Удалив конструктор копий, вы прямо сообщите компилятору, что экземпляры этого класса не могут быть скопированы
	Window& operator=(const Window&) = delete; //Явно удаляет оператора назначения копий для класса
	
	//вызов нашей графики
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
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //функция обработки сообщений
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //функция обработчик
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);					   //функция для обработки различных сообщений
private:
	int width; //ширина окна
	int height; //высота окна
	HWND hWnd; //экземпляр созданного окна
	std::unique_ptr<Graphics>pGfx; //d3d11 Графика
};
Window::WinClass Window::WinClass::wndClass; //объеявляем статическую функцию экземпляра

//Добавление функций в функцию WinMain 
Window::WinClass::WinClass():hInst(GetModuleHandle(nullptr)) // GetModuleHandle(LPCSTR lpModuleName) извлекает дескриптор модуля для указанного модуля
{
	WNDCLASSEX wc = { 0 }; // Структура содержит сведения о окне
	wc.cbSize = sizeof(wc);// Размер этой структуры в байтах
	wc.style = CS_OWNDC;// Этот элемент может быть любым сочетанием стилей классов
	wc.lpfnWndProc = HandleMsgSetup;// Указатель на процедуру окна
	wc.cbClsExtra = 0;// Количество дополнительных байтов, выделяемых после структуры класса окна
	wc.cbWndExtra = 0;// Количество дополнительных байтов, выделяемых после экземпляра окна
	wc.hInstance = GetInstance();// Дескриптор экземпляра, содержащего процедуру окна для класса
	wc.hIcon = static_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));// Дескриптор значка класса. Этот элемент должен быть дескриптором ресурса значка
	wc.hCursor = nullptr;// Дескриптор курсора класса. Этот элемент должен быть дескриптором ресурса курсора
	wc.hbrBackground = nullptr;// Дескриптор фоновой кисти класса. Этот элемент может быть дескриптором кисти, используемой для рисования фона
	wc.lpszMenuName = nullptr;// Указатель на строку символов, указывает имя ресурса меню класса, так как имя отображается в файле ресурса
	wc.lpszClassName = GetName();// Является строкой, он указывает имя класса окна. Имя класса может быть любым именем, зарегистрированным в RegisterClass
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0)); // Дескриптор небольшого значка, связанного с классом окна
	RegisterClassEx(&wc);// Регистрирует класс окна для последующего использования в вызовах функции CreateWindow получется как значение ATOM
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) // сообщение перед созданием окна то-есть перед WM_CREATE
	{ 
		// reinterpret_cast <type - id> (expression)
		// Позволяет преобразовывать любой указатель в указатель любого другого типа. 
		// Также позволяет преобразовывать любой целочисленный тип в любой тип указателя и наоборот

		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam); // Определяет параметры инициализации, передаваемые в процедуру окна приложения.
		// static_cast Преобразует выражение в тип идентификатора типа, основываясь только на типах, присутствующих в выражении
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams); // пермещает все параметры в класс pWnd 
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));//Изменяет атрибут указанного окна. Функция также задает значение по указанному смещением в дополнительном окне памяти
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));// изменяем атребуты с применением уже с изменненными параметрами от сообщений
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);// возвращаем наш экземпляр с сообщенимем при создании
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);// вернем базовое состояние
};

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));//пробразует данные window в указатель параметров с сообщениями
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);//возвращает все исходые сообщения в виде параметра
};

// Windows также должно иметь функцию window-procedure. Эта функция вызывается, WndProc 
// В этой функции вы пишете код для обработки сообщений
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) //код сообщения
	{
	case WM_CLOSE: //код отправленного сообщения
		PostQuitMessage(0); //отправка сообщения на закрытия окна в очередь сообщений с кодом 0
		return 0;
	
		//тут много прочих сообщений, в документации их оооочень много около 1000+ сообщений
		

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);//Эта функция гарантирует обработку каждого сообщения. вызывается с теми же параметрами, что и процедура окна. 
													//так же есть функции  CallWindowProc 	Передает сведения о сообщении в указанную процедуру окна. 
														//WindowProc Определяемая приложением функция, которая обрабатывает сообщения, отправленные в окно.
		break;
	}
};