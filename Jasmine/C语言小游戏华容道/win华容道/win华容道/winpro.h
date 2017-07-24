#ifndef __WIN_PRO_H__
#define __WIN_PRO_H__

#define IDC_HAND         MAKEINTRESOURCE(32649) 

//#include "resource.h"
//#include "hrd.h"
#include "winlay.h"
#include <windows.h>

//主窗口处理函数 
LRESULT CALLBACK
WinProcedure(
	HWND,
	UINT,
	WPARAM,
	LPARAM
);
#endif
