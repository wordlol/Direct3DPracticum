//#include "windows.h"
//#include "string"
//#include <sstream>
//
////����������� ���������������� ��������� ���� ��� ��������� ������������ ��������� ����
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    //switch (msg) //�������������� ��������
//    //{
//    //case WM_CLOSE: //�� �������� �� ��� ��������
//    //     {
//    //        PostQuitMessage(69); //���������� ��������� ��� ������ �������� � ������� ��� ������
//    //     }
//    //        break;
//    //case WM_KEYDOWN: //���� ����� ����� ��������� ����� 1000+ ������� �������� ��� ������ ������� ����
//    //    if (wParam = 'F') //������
//    //    {
//    //        SetWindowText(hWnd, L"DSADASD");
//    //    }
//    //    break;
//    //case WM_CHAR: //��������� ��� ����� ������
//    //{
//    //    static std::string title;
//    //    title.push_back(wParam); //���������� � ����� ������ �����
//    //    std::wstring stemp = std::wstring(title.begin(), title.end());//����������� ����� �� string � wchar_t (LPCWSTR lpString)
//    //    SetWindowText(hWnd, stemp.c_str());
//
//    //}
//    //    break;
//    //case WM_LBUTTONDOWN: //����� ������ ����
//    //{
//    //    POINTS Pt = MAKEPOINTS(lParam); //���������� ����� ����
//    //    std::ostringstream oss; //�� ������ ����� ���� ��� ������� ��� ������ ��� ��� ��� ��������� � ������ ��� ����
//    //    oss << "(" << Pt.x << "," << Pt.y << ")";
//    //    const std::string title = oss.str(); // �� ����� ��� �������������� ����� ����������� ������
//    //    std::wstring stemp = std::wstring(title.begin(), title.end()); //������ � ����� ������ �� �������� ��������������
//    //    SetWindowText(hWnd, stemp.c_str());
//    //}
//    //break;
//    //}
//    return DefWindowProc(hWnd, msg, wParam, lParam); //���������� ������� ��������� ����
//}
//
//
//// callback ���������� � ������ ������� �� ��� � �++
//int CALLBACK WinMain(
//    HINSTANCE hInstance,//* //��������� �� �������� ������� �������� ���� ����� ���������
//    HINSTANCE hPrevInstance,//* ������� ���������
//    LPSTR lpCmdLine,//��������� ������ ��� ���������
//    int nShowCmd //��� ������ ������������ ���� ��� �������
//)
//{
//    //���������� �� �� ��������
//    /*UINT      cbSize; ������ ���������
//    UINT      style; ��������� ����� �������
//    WNDPROC   lpfnWndProc; ��������� �� ������� window pro� ��������� ��������� ����
//    int       cbClsExtra; �������� �������������� ����� � ������
//    int       cbWndExtra; �������� ����� ��� ����� ������� �� �������
//    HINSTANCE hInstance; HINSTANCE hInstance �� winmain
//    HICON     hIcon;
//    HCURSOR   hCursor;
//    HBRUSH    hbrBackground;
//    LPCWSTR   lpszMenuName; ���� ����
//    LPCWSTR   lpszClassName; �������� ������ ������� �� ���������� ��� �����������
//    HICON     hIconSm;*/ //������ ��� ����
//    WNDCLASSEX wc = {0}; //��������� ������� �� ��������� ��� �������� �� ��������� � �����������
//    const wchar_t ClassName = (wchar_t)"Direct3DPracticum"; // ��� � ���� �������� ������ ����
//    wc.cbSize = sizeof(wc);
//    wc.style = CS_OWNDC;
//    wc.lpfnWndProc = WndProc;
//    wc.cbClsExtra = 0;
//    wc.cbWndExtra = 0;
//    wc.hInstance = hInstance;
//    wc.hIcon = nullptr;
//    wc.hCursor = nullptr;
//    wc.hbrBackground = nullptr;
//    wc.lpszMenuName = nullptr;
//    wc.lpszClassName = &ClassName;
//    wc.hIconSm = nullptr;
//    RegisterClassEx(&wc); //����������� ������ ����
//    
//    /*HWND CreateWindowExA(
//        DWORD     dwExStyle, ����������� �����
//        LPCSTR    lpClassName, ��� ������
//        LPCSTR    lpWindowName, ��� ����
//        DWORD     dwStyle, ��� ������� �����
//        int       X, ������� �� �
//        int       Y, ������� �� y
//        int       nWidth, ������ ����
//        int       nHeight, ������ ����
//        HWND      hWndParent, �������� ����
//        HMENU     hMenu, ���� �� ����
//        HINSTANCE hInstance, ��������� ���� �� winmain
//        LPVOID    lpParam ��������� ���������������� ������
//    );*/
//
//    //�������� ���� ��� ����� ���������� ���������� ���� ������ ��� ��������� � �����������
//    HWND hWnd = CreateWindowEx(
//        0,
//        &ClassName,
//        L"Happy window",
//        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//        0,
//        0,
//        600,
//        600,
//        nullptr,
//        nullptr,
//        hInstance,
//        nullptr
//        );
//
//    //�������� ����    
//    ShowWindow(hWnd, SW_SHOW);
//    
//    //��������� msg
//   /* BOOL GetMessage(
//        LPMSG lpMsg,  ��������� �� ��������� 
//        HWND  hWnd, ���������� ���� �� ���� ��������� ���������
//        UINT  wMsgFilterMin, �������� ������� ��������� ������� �� ����� ������ �� �������
//        UINT  wMsgFilterMax
//    );*/ //�������� ��������� �� ���������� ���������� ���������� �� ��� ����� 1 ����� 0 � ���� ������ �� -1
//
//   /* typedef struct tagMSG {
//        hwnd; ���� ����� ��������
//        message; ����� ��������� ��� ���������� ��� ����
//        wParam; 32 ������ ��������
//        lParam; 32 ������ ��������
//        time; ����� ���������
//        pt; ����� ��������� ��������� �������
//        lPrivate; ������ ���������
//    } MSG, * PMSG, * NPMSG, * LPMSG;*/
//
//    // Message pump
//    MSG msg;
//    BOOL gResult; //����� ��� ��������� ���������
//    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
//    {
//        TranslateMessage(&msg); //���� ��� > 0 ������� ��������� �� ������� ���� ���������
//        DispatchMessage(&msg); //�������� ���������
//    }
//    if (gResult == -1)
//    {
//        return -1; //���� ����� ������ �� ����� ���
//    }
//    else
//    {
//        return msg.wParam; // ���� ����� �������� ����� ���� �� ������� ����� ���� � ����� ������ ��� 69
//    }
//
//
//
//
//
//
//
//
//
//
//	return 0;
//}
