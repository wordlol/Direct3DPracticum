#pragma once
#include "WindowsFrameWork.h"

class App /// класс приложени€ нужен дл€ упращени€ работы с приложением и отделением потока логики приложени€ от обработки сообщений
{
public:
	App():wnd(1280, 720, L"3DProgramm"){} /// это способ создание объекта другово класса, при помощи базового контруктора этого класса
	int Go()
	{
		while (true)
		{
			if (const auto ecode = Window::ProcessMessages()) /// новый цикл обработки сообщений
			{
				return *ecode; /// указатель на опциональный ответ сообщени€
			}
			DoFrame(); /// цикл выполнени€ логики приложени€
		}
	};
private:
	void DoFrame()
	{
		float c = sin(timer.Reack())/2.0f+0.5f; /// синусоидальна€ функци€
		wnd.Gfx().EndFrame(); /// вывод отрисовки экрана
		wnd.Gfx().ClearBuffer(0.2, c, 0.6f); /// отрисовка на экране rgb колорита
	};
private:
	Window wnd; /// объект класса которые будет построен в другом месте этого класса
	Timer timer; /// стандартный таймер хроно
};
