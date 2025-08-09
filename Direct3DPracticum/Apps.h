#pragma once
#include "WindowsFrameWork.h"

class App
{
public:
	App():wnd(1280, 720, L"3DProgramm"){}
	int Go()
	{
		while (true)
		{
			if (const auto ecode = Window::ProcessMessages())
			{
				return *ecode;
			}
			DoFrame();
		}
	};
private:
	void DoFrame()
	{
		float c = sin(timer.Reack())/2.0f+0.5f;
		wnd.Gfx().EndFrame();
		wnd.Gfx().ClearBuffer(0.2, c, 0.6f);
	};
private:
	Window wnd; //создание виндовс окна;
	Timer timer;
};

//старый способ отправки сообщений
//MSG msg; //Содержит информацию сообщения из очереди сообщений потока
//BOOL gResult; //получает ответ из GetMessage
//while ((gResult = GetMessage(&msg, nullptr, 0, 0)) != 0) //стандартный цикл приемки сообщений, пока результат не будет нулевым или ошибкой
//{
//
//	if (gResult == -1)
//	{
//		return -1; //Вернет ошибку приложения
//	}
//	else
//	{
//		TranslateMessage(&msg);// Преобразует сообщения с виртуальным ключом в символьные сообщения
//		// Символьные сообщения помещаются в очередь сообщений вызывающего потока, чтобы их можно было прочитать при следующем вызове функции GetMessage или PeekMessage 
//
//		DispatchMessage(&msg);// Отправляет сообщение в процедуру окна. Обычно он используется для отправки сообщения, полученного функцией GetMessage
//
//
//
//		//временное решение располагать отрисовку здесь
//		float c = sin(tTimer.Reack()) / 2.0f + 0.5f;
//
//	}
//}
///*Если функция завершается успешно, завершая получение сообщения WM_QUIT,
//оно должно вернуть значение выхода, содержащееся в параметре wParam сообщения.
//Если функция завершается перед вводом цикла сообщений, она должна возвращать ноль.*/
//return msg.wParam;