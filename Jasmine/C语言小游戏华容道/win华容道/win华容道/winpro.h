#ifndef __WIN_PRO_H__
#define __WIN_PRO_H__

#define IDC_HAND         MAKEINTRESOURCE(32649) 

//#include "resource.h"
//#include "hrd.h"
#include "winlay.h"
#include <windows.h>

//�����ڴ����� 
LRESULT CALLBACK
WinProcedure(
	HWND,
	UINT,
	WPARAM,
	LPARAM
);
#endif
