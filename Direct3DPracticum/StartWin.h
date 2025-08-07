#pragma once
//������ ��� ��������� ���������� windows.h �� ������
//��������� ���������  �������� ������� ������������ �����
//��������� ��� �����

#define _WIN32_WINNT 0x0A00 //������� ����������� ������ ������������ �������, �������������� �����

#include <sdkddkver.h> //���� ����� ����� ����� �������������� ����� ������� ����������� �� ����� ������ �������

//��� ����� ������� ����� ���������� ������ ��� ���������� ����������� ����� Window.h
#define WIN32_LEAN_AND_MEAN //����� ��������� ����� API, ��� ������������, DDE, RPC, �������� � ������ Windows. (��� ������� ���������� ���� Window.h)
#define NOGDICAPMASKS     //- CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOSYSMETRICS	  //- SM_ *
#define NOMENUS			  //- MF_ *
#define NOICONS			  //- IDI_ *
#define NOSYSCOMMANDS	  //- SC_ *
#define NOVIRTUALKEYCODES //- VK_ *
#define NOKEYSTATES		  //- MK_ *
#define NORASTEROPS		  //- �������� � ��������� � ���������� ��������
#define OEMRESOURCE	      //- �������� �������� OEM-��������������
#define NOATOM			  //- Atom ��������� ���������
#define NOCLIPBOARD		  //- ��������� ������ � ������� ������
#define NOCOLOR		      //- ����� ������
#define NOCTLMGR		  //- ��������� ���������� � �������
#define NODRAWTEXT		  //- DrawText() and DT_ *
#define NOGDI			  //- All GDI ����������� � ���������
#define NOKERNEL		  //- All KERNEL ����������� � ���������
#define NONLS			  //- All NLS ����������� � ���������
#define NOMB			  //- MB_ * and MessageBox()
#define NOMEMMGR		  //- GMEM_*, LMEM_*, GHND, LHND, ��������� � ���� ���������
#define NOMETAFILE		  //- typedef METAFILEPICT
#define NOMINMAX		  //- Macros min(a, b) and max(a, b)
#define NOOPENFILE		  //- OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL		  //- SB_ * � ��������� ���������
#define NOSERVICE		  //- All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND			  //- ��������� ���������� ������
#define NOTEXTMETRIC	  //- typedef TEXTMETRIC � ��������� � ���� ���������
#define NOWH			  //- SetWindowsHook and WH_ *
#define NOCOMM			  //- COMM driver ���������
#define NOKANJI			  //- Kanji support stuff.
#define NOHELP		      //- ��������� ��������� �������
#define NOPROFILER		  //- Profiler interface.
#define NODEFERWINDOWPOS  //- DeferWindowPos routines
#define NOMCX		      //- ���������� ������������ ������
#define NOTAPE			  //- ��� ����������������
#define NOIMAGE			  //- ��� ����� ���������� ������������ ������������ ������� (PE) � ������ ������� ������� ������ �������� (COFF)
#define NOPROXYSTUB		  //- ��� ������-������� ��� �������� ��� ����������������� ����������
#define NORPC			  //- ����������� ����� ��������� ��������� 

#define STRICT //- ��������� STRICT �������������� ��������� ���� ������ ���, ����� ���������� �� �������� ������������ �������� ������ ���� ������� ��� ������ ����������

#include <Windows.h>
#include "resource.h"