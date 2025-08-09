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
	Window wnd; //�������� ������� ����;
	Timer timer;
};

//������ ������ �������� ���������
//MSG msg; //�������� ���������� ��������� �� ������� ��������� ������
//BOOL gResult; //�������� ����� �� GetMessage
//while ((gResult = GetMessage(&msg, nullptr, 0, 0)) != 0) //����������� ���� ������� ���������, ���� ��������� �� ����� ������� ��� �������
//{
//
//	if (gResult == -1)
//	{
//		return -1; //������ ������ ����������
//	}
//	else
//	{
//		TranslateMessage(&msg);// ����������� ��������� � ����������� ������ � ���������� ���������
//		// ���������� ��������� ���������� � ������� ��������� ����������� ������, ����� �� ����� ���� ��������� ��� ��������� ������ ������� GetMessage ��� PeekMessage 
//
//		DispatchMessage(&msg);// ���������� ��������� � ��������� ����. ������ �� ������������ ��� �������� ���������, ����������� �������� GetMessage
//
//
//
//		//��������� ������� ����������� ��������� �����
//		float c = sin(tTimer.Reack()) / 2.0f + 0.5f;
//
//	}
//}
///*���� ������� ����������� �������, �������� ��������� ��������� WM_QUIT,
//��� ������ ������� �������� ������, ������������ � ��������� wParam ���������.
//���� ������� ����������� ����� ������ ����� ���������, ��� ������ ���������� ����.*/
//return msg.wParam;