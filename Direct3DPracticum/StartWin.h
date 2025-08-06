#pragma once
//пержде чем запускать библиотеку windows.h мы должны
//отключить несколько  макросов которые потенциально могут
//испортить нам жизнь

//#define _WIN32_WINNT_WIN10 0x0A00 //это наш виндовс 10 не знаю как он работает на 11 но вроде норм
//
//#include <sdkddkver.h> //используются для управления тем, какие функции, константы включаются в ваш код из заголовков Windows
//#define WIN32_LEAN_AND_MEAN
//#define NOGDICAPMASKS
//#define NOSYSMETRICS
//#define NOMENUS
//#define NOICONS
//#define NOSYSCOMMANDS
//#define NORASTEROPS
//#define OEMRESOURCE
//#define NOATOM
//#define NOCLIPBOARD
//#define NOCOLOR
//#define NOCTLMGR
//#define NODRAWTEXT
//#define NOKERNEL
//#define NONLS
//#define NOMEMMGR
//#define NOMETAFILE
//#define NOMINMAX
//#define NOOPENFILE
//#define NOSCROLL
//#define NOSERVICE
//#define NOSOUND
//#define NOTEXTMETRIC
//#define NOWH
//#define NOCOMM
//#define NOKANJI
//#define NOHELP
//#define NOPROFILER
//#define NODEFERWINDOWPOS
//#define NOMCX
//#define NORPC
//#define NOPROXYSTUB
//#define NOIMAGE
//#define NOTAPE
//
//#define STRICT

#include <Windows.h>