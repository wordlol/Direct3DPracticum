#pragma once
#include "WindowsFrameWork.h"

class App /// ����� ���������� ����� ��� ��������� ������ � ����������� � ���������� ������ ������ ���������� �� ��������� ���������
{
public:
	App():wnd(1280, 720, L"3DProgramm"){} /// ��� ������ �������� ������� ������� ������, ��� ������ �������� ����������� ����� ������
	int Go()
	{
		while (true)
		{
			if (const auto ecode = Window::ProcessMessages()) /// ����� ���� ��������� ���������
			{
				return *ecode; /// ��������� �� ������������ ����� ���������
			}
			DoFrame(); /// ���� ���������� ������ ����������
		}
	};
private:
	void DoFrame()
	{
		float c = sin(timer.Reack())/2.0f+0.5f; /// �������������� �������
		wnd.Gfx().EndFrame(); /// ����� ��������� ������
		wnd.Gfx().ClearBuffer(0.2, c, 0.6f); /// ��������� �� ������ rgb ��������
	};
private:
	Window wnd; /// ������ ������ ������� ����� �������� � ������ ����� ����� ������
	Timer timer; /// ����������� ������ �����
};
