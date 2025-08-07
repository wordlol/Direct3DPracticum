#pragma once
//пержде чем запускать библиотеку windows.h мы должны
//отключить несколько  макросов которые потенциально могут
//испортить нам жизнь

#define _WIN32_WINNT 0x0A00 //указать минимальную версию операционной системы, поддерживаемый кодом

#include <sdkddkver.h> //этот хедер нужен чтобы переопределять какие макросы переключать от вашей версии виндовс

//это самый бызовый набор исключения файлов для уменьшения включаемого файла Window.h
#define WIN32_LEAN_AND_MEAN //чтобы исключить такие API, как криптография, DDE, RPC, оболочка и сокеты Windows. (это уменшит включаемый файл Window.h)
#define NOGDICAPMASKS     //- CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOSYSMETRICS	  //- SM_ *
#define NOMENUS			  //- MF_ *
#define NOICONS			  //- IDI_ *
#define NOSYSCOMMANDS	  //- SC_ *
#define NOVIRTUALKEYCODES //- VK_ *
#define NOKEYSTATES		  //- MK_ *
#define NORASTEROPS		  //- Операции с бинарными и третичными растрами
#define OEMRESOURCE	      //- Ценности ресурсов OEM-производителей
#define NOATOM			  //- Atom Процедуры менеджера
#define NOCLIPBOARD		  //- Процедуры работы с буфером обмена
#define NOCOLOR		      //- Цвета экрана
#define NOCTLMGR		  //- Процедуры управления и диалога
#define NODRAWTEXT		  //- DrawText() and DT_ *
#define NOGDI			  //- All GDI определения и процедуры
#define NOKERNEL		  //- All KERNEL определения и процедуры
#define NONLS			  //- All NLS определения и процедуры
#define NOMB			  //- MB_ * and MessageBox()
#define NOMEMMGR		  //- GMEM_*, LMEM_*, GHND, LHND, связанные с ними процедуры
#define NOMETAFILE		  //- typedef METAFILEPICT
#define NOMINMAX		  //- Macros min(a, b) and max(a, b)
#define NOOPENFILE		  //- OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL		  //- SB_ * и процедуры прокрутки
#define NOSERVICE		  //- All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND			  //- Процедуры управления звуком
#define NOTEXTMETRIC	  //- typedef TEXTMETRIC и связанные с ними процедуры
#define NOWH			  //- SetWindowsHook and WH_ *
#define NOCOMM			  //- COMM driver процедуры
#define NOKANJI			  //- Kanji support stuff.
#define NOHELP		      //- Интерфейс механизма справки
#define NOPROFILER		  //- Profiler interface.
#define NODEFERWINDOWPOS  //- DeferWindowPos routines
#define NOMCX		      //- Расширения конфигурации модема
#define NOTAPE			  //- Тип позиционирования
#define NOIMAGE			  //- Эти файлы называются переносимыми исполняемыми файлами (PE) и общими файлами формата файлов объектов (COFF)
#define NOPROXYSTUB		  //- Код прокси-сервера или заглушки для пользовательского интерфейса
#define NORPC			  //- Асинхронный вызов удаленной процедуры 

#define STRICT //- Включение STRICT переопределяет некоторые типы данных так, чтобы компилятор не разрешал присваивание значений одного типа другому без явного приведения

#include <Windows.h>
#include "resource.h"