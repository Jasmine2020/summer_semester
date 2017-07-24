// 引用的头文件
#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include "winlay.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

// 画图时使用的表示蛇和食物的圆形的直径像素点个数。
#define CELL_PIXEL			80

// 用来绘图的颜色
#define COLOR_GENERAL_1			RGB(255,215,0)//orange
#define COLOR_GENERAL_2			RGB(238,180,180)//pink
#define COLOR_GENERAL_3			RGB(205,197,191)//gray
#define COLOR_GENERAL_4			RGB(186,85,211)//purple
#define COLOR_GENERAL_5			RGB(32,178,170)//blue
#define COLOR_CMAN              RGB(255,0,0)//red
#define COLOR_SOLIDER		RGB(127,255,0)//green
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(173,216,230)

#define IMAGINE_PAPER   TEXT("song.bmp")
#define IMAGINE_DARGON	TEXT("deng.bmp")
#define IMAGINE_DOG		TEXT("huang.bmp")
#define IMAGINE_KNIVE	TEXT("lian.bmp")
#define IMAGINE_HUANG	TEXT("huaniao.bmp")
#define IMAGINE_LIGHT	TEXT("lu.bmp")
#define IMAGINE_HEXIN	TEXT("gou.bmp")

Pgame_coord soldier[4];
Pgame_coord general;
Pgame_coord cman;

/********************************************************************************
* ##########关于Windows数据类型##########
*
* Windows在C语言的基础上定义了很多Windows特有的类型。都是通过C语言关键字typedef定义的。
* Windows类型都是全大写。
*
* DWORD LPSTR WPARAM LPARAM HWND等
* 其中，以'H'大头的数据类型都是句柄
*
*******************************************************************************/

/*******************************************************************************
* ##########   关于句柄    ##########
*
* 句柄是Windows系统中的基础数据类型
* 句柄是系统对象的标识符，用来唯一表示一个系统对象
* 例如：文件、窗口、线程、计时器等等。
* 句柄的类型也有细分，基础的句柄如HANDLE，窗口句柄HWND，GDI画刷句柄HBRUSH等。
* 所有以H开头的类型基本都是句柄类型。
*
*******************************************************************************/

// 全局变量
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;
int nCode[2];
int count = 0;
int step=0;


// 函数声明
HBITMAP hpicture0;
HBITMAP hpicture[5];
HBITMAP picture;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


/*******************************************************************************
* ##########   入口函数WinMain    ##########
*
* Windows应用程序的入口函数是WinMain函数，其地位和作用类似标准C语言的main函数
*
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance, // 父进程的程序实例句柄
	LPSTR lpCmdLine,  // 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)   // 用于指明窗口是否需要显示的参数。
{

	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = "MainMenu";
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// 窗口类名，必须是已经注册了的窗口类
		TEXT("华容道"),		// title-bar string 
		WS_CAPTION | WS_SYSMENU,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);

	mciSendString(TEXT("close Lil'Goldfish.wav"), 0, 0, 0);
	mciSendString(TEXT("play Lil'Goldfish.wav"), NULL, NULL, NULL);

	/*******************************************************************************
	* ##########   MSG类型和消息    ##########
	*
	* Windows窗口应用程序是一种消息驱动的程序框架。
	* Windows窗口应用程序运行以后，其主线程就一直处于
	* "等待消息--获取消息--效应消息" 的循环之中，直到程序退出。
	*
	* 所谓消息是Windows系统特有的一种系统对象和机制，
	* 是操作系统对某些系统状态（如时钟）和用户操作（如鼠标点击）产生的系统中断进行封装以后，
	* 可以发送到应用程序，并由应用程序进行处理的用户态对象。
	*
	* "MSG"就是用来表示"消息"的数据类型。 这里定义了一个MSG类型的变量，变量名为msg
	*
	*******************************************************************************/


	// 以下进入消息循环。获取消息--翻译消息--分配消息（由窗口的消息处理函数来处理消息）
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void GamePaint(HWND hwnd)
{
	/*******************************************************************************
	* ##########   关于 GDI    ##########
	*
	* GDI的全称是Graphics Device Interface，图形设备接口。
	* GDI是Windows系统中最基础的图形图像接口，我们在这里演示的是GDI中最基础的部分，
	* 但是对于编写贪吃蛇这样的小游戏已经足够用了。
	*
	* 来看GDI最基础的三个概念：
	* 1、DC：DC的全称是Device Context，绘制操作在此进行。可以类比理解为一块画布，对应屏幕的一个区域。
	*      GDI的绘制操作必须在一个DC上进行，因此第一步就是得到DC的句柄，BeginPaint或者GetDC函数。
	* 2、GDI对象：包括PEN、BRUSH、FONT等，每一种绘制操作都会使用到一个或者多个GDI对象，
	*      所以，在绘制操作之前必须的一个操作是将绘制所用的GDI对象放入DC中，使用SelectObject函数完成。
	* 3、绘制操作：即在DC上使用被选择如DC中的GDI对象绘制图形、线条、文字等。
	*      如LineTo画出线条、Ellipse画出(椭)圆、Rectangle画出矩形、TextOut输出文字
	*
	* 使用GDI输出各类图像有其特定的流程，如下:
	*******************************************************************************/

	HPEN hpen;
	//HBRUSH hbrush;
	HDC hdc, hdcmem;

	HDC hdcBitmapSrc;
	BITMAP bmp;

	HBITMAP hbmMem;

	HPEN hPenBoundary;
	HPEN hpenChoice;
	HPEN hOldPen;

	HBRUSH hbrushSolider;
	HBRUSH hBrushGeneral[5];
	HBRUSH hBrushCMAN;
	HBRUSH hOldBrush;

	HFONT hFont, hOldFont;

	RECT rect;

	int i, m;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	// 创建需要用到的PEN和BRUSH
	hpen = CreatePen(PS_NULL, 0, COLOR_BOUNDARY);  // PEN， PS_NULL表示不可见
	hBrushCMAN = CreateSolidBrush(COLOR_CMAN);
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	hpenChoice = CreatePen(0, 3, RGB(0,0,0));

	hbrushSolider = CreateSolidBrush(COLOR_SOLIDER);
	hBrushGeneral[0] = CreateSolidBrush(COLOR_GENERAL_1);
	hBrushGeneral[1] = CreateSolidBrush(COLOR_GENERAL_2);
	hBrushGeneral[2] = CreateSolidBrush(COLOR_GENERAL_3);
	hBrushGeneral[3] = CreateSolidBrush(COLOR_GENERAL_4);
	hBrushGeneral[4] = CreateSolidBrush(COLOR_GENERAL_5);
	hBrushCMAN = CreateSolidBrush(COLOR_CMAN);

	hdcBitmapSrc = CreateCompatibleDC(hdc);


	/*******************************************************************************
	* #############  画背景  ################
	*
	*******************************************************************************/
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	/*******************************************************************************
	* #############  画小兵  ################
	*
	*******************************************************************************/
	//hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushSolider);
	//hOldPen = (HPEN)SelectObject(hdcmem, hpen);
	//for (i = 0;i < 4;i++)
	//{
	//	soldier[i] = GetSoldier(i);

	//	// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
	//	Rectangle(hdcmem,
	//		soldier[i]->x * CELL_PIXEL + rectBoundary.left,
	//		soldier[i]->y * CELL_PIXEL + rectBoundary.top,
	//		(soldier[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
	//		(soldier[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	//}

	// 将画图需要用的PEN和BRUSH选择到DC中
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	SelectObject(hdcBitmapSrc, hpicture0);
	GetObject(hpicture0, sizeof(BITMAP), &bmp);

	for (i = 0;i < 4;i++)
	{
		StretchBlt(hdcmem,
			solider[i].x * CELL_PIXEL + rectBoundary.left,
			solider[i].y * CELL_PIXEL + rectBoundary.top,
			CELL_PIXEL, CELL_PIXEL,
			hdcBitmapSrc,
			0, 0, bmp.bmWidth, bmp.bmHeight,
			SRCCOPY);
	}


	/*******************************************************************************
	* #############  画将  ################
	*
	*******************************************************************************/
	
	//for (m = 0;m <= 4;m++)
	//{
	//	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushGeneral[m]);
	//	for (i = 0;i < 2;i++)
	//	{
	//		general = GetGeneral(m,i);

	//		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
	//		Rectangle(hdcmem,
	//			general->x * CELL_PIXEL + rectBoundary.left,
	//			general->y * CELL_PIXEL + rectBoundary.top,
	//			(general->x + 1)*CELL_PIXEL + rectBoundary.left,
	//			(general->y + 1)*CELL_PIXEL + rectBoundary.top);
	//	}
	//}

	for (m = 0;m <= 4;m++)
	{
		SelectObject(hdcBitmapSrc, hpicture[m]);
		GetObject(hpicture[m], sizeof(BITMAP), &bmp);
		if (m != 3)
		{
			StretchBlt(hdcmem,
				General[m][0].x * CELL_PIXEL + rectBoundary.left,
				General[m][0].y * CELL_PIXEL + rectBoundary.top,
				CELL_PIXEL, CELL_PIXEL * 2,
				hdcBitmapSrc,
				0, 0, bmp.bmWidth, bmp.bmHeight,
				SRCCOPY);
		}
		else
		{
			StretchBlt(hdcmem,
				General[m][0].x * CELL_PIXEL + rectBoundary.left,
				General[m][0].y * CELL_PIXEL + rectBoundary.top,
				CELL_PIXEL*2, CELL_PIXEL,
				hdcBitmapSrc,
				0, 0, bmp.bmWidth, bmp.bmHeight,
				SRCCOPY);
		}
		
	}

	/*******************************************************************************
	* #############  画曹操  ################
	*
	*******************************************************************************/
	//hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushCMAN);
	//for (i = 0;i < 4;i++)
	//{
	//	cman = GetCMAN(i);

	//	// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
	//	Rectangle(hdcmem,
	//		cman->x * CELL_PIXEL + rectBoundary.left,
	//		cman->y * CELL_PIXEL + rectBoundary.top,
	//		(cman->x + 1)*CELL_PIXEL + rectBoundary.left,
	//		(cman->y + 1)*CELL_PIXEL + rectBoundary.top);
	//}
	
	SelectObject(hdcBitmapSrc, picture);
	GetObject(picture, sizeof(BITMAP), &bmp);
	StretchBlt(hdcmem,
		CMAN[0].x * CELL_PIXEL + rectBoundary.left,
		CMAN[0].y * CELL_PIXEL + rectBoundary.top,
		CELL_PIXEL*2, CELL_PIXEL*2,
		hdcBitmapSrc,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);
	


	//画边框
	for (i = 0;i < 4;i++)
	{
		if (solider[i].select == 1)
		{
			SelectObject(hdcmem, hpenChoice);
			MoveToEx(hdcmem, solider[i].x * CELL_PIXEL + 22,
				solider[i].y * CELL_PIXEL + 22, NULL);
			LineTo(hdcmem, solider[i].x * CELL_PIXEL + 22, (solider[i].y + 1)*CELL_PIXEL + rectBoundary.top - 2);
			LineTo(hdcmem, (solider[i].x + 1)*CELL_PIXEL + rectBoundary.left - 2, (solider[i].y + 1)*CELL_PIXEL + rectBoundary.top - 2);
			LineTo(hdcmem, (solider[i].x + 1)*CELL_PIXEL + rectBoundary.left - 2, solider[i].y * CELL_PIXEL + rectBoundary.top + 2);
			LineTo(hdcmem, solider[i].x * CELL_PIXEL + 22, solider[i].y * CELL_PIXEL + rectBoundary.top + 2);
			solider[i].select = 0;
		}
	}
	for (m = 0;m < 5;m++)
	{
		if (General[m][0].select == 1)
		{
			SelectObject(hdcmem, hpenChoice);
			MoveToEx(hdcmem, General[m][0].x * CELL_PIXEL + 22,
				General[m][0].y * CELL_PIXEL + 22, NULL);
			if (m != 3)
			{//竖将
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, (General[m][0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 1)*CELL_PIXEL + rectBoundary.left - 2, (General[m][0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 1)*CELL_PIXEL + rectBoundary.left - 2, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
			}
			else
			{//横将
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, (General[m][0].y + 1)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 2)*CELL_PIXEL + rectBoundary.left - 2, (General[m][0].y + 1)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 2)*CELL_PIXEL + rectBoundary.left - 2, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
			}
			General[m][0].select = 0;
		}
	}
	if (CMAN[0].select == 1)
	{
		SelectObject(hdcmem, hpenChoice);
		MoveToEx(hdcmem, CMAN[0].x * CELL_PIXEL + 22,
			CMAN[0].y * CELL_PIXEL + 22, NULL);
		LineTo(hdcmem, CMAN[0].x * CELL_PIXEL + 22, (CMAN[0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
		LineTo(hdcmem, (CMAN[0].x + 2)*CELL_PIXEL + rectBoundary.left - 2, (CMAN[0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
		LineTo(hdcmem, (CMAN[0].x + 2)*CELL_PIXEL + rectBoundary.left - 2, CMAN[0].y * CELL_PIXEL + rectBoundary.top + 2);
		LineTo(hdcmem, CMAN[0].x * CELL_PIXEL + 22, CMAN[0].y * CELL_PIXEL + rectBoundary.top + 2);
		CMAN[0].select = 0;
	}
	

	/*******************************************************************************
	* #############  画墙  ################
	*
	*******************************************************************************/

	SelectObject(hdcmem, hPenBoundary);

	// 将PEN移动到需要绘制的方框的左上角
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// 画了一个方框。演示LineTo函数
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	/*******************************************************************************
	* #############  写一行字  ################
	*
	*******************************************************************************/

	// 创建了一个字体对象
	hFont = CreateFont(38, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// 将这个FONT对象放入DC中
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, TEXT("拯救大天狗 Step %d"), step);
		// 设置输出颜色
		SetTextColor(hdcmem, COLOR_TEXT);
		// 输出字符串。
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		// 输出完成，将原来的字体对象放回DC中
		SelectObject(hdcmem, hOldFont);
	}

	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	/*******************************************************************************
	* #############  回收和释放资源  ################
	*
	*******************************************************************************/
	// 回收资源
	// DeleteObject 释放GDI对象
	DeleteDC(hdcmem);
	DeleteDC(hdc);
	DeleteDC(hdcBitmapSrc);
	DeleteObject(hBrushCMAN);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hpenChoice);
	DeleteObject(hBrushGeneral);
	/*******************************************************************************
	* #############  ReleaseDC 函数  ################
	* 释放占用的DC等系统资源。
	*******************************************************************************/
	ReleaseDC(hwnd, hdc);
}


/*******************************************************************************
* ##########   根据游戏界面的坐标系大小设置游戏窗口大小    ##########
*******************************************************************************/

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	Pgame_coord pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left = 20;
	rectBoundary.top = 20;
	rectBoundary.right = 20 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 20 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // 保存边界和左右两边边框相等。
		rectBoundary.bottom + 120, //给积分信息留出显示空间。
		TRUE);
}


/*******************************************************************************
* ##########   消息处理回调函数    ##########
*
* 当窗口每收到一个消息，此函数就被调用一次。
* 由于消息的到达不确定性，因此，消息函数的调用是回调的，即：
* 应用程序定义好消息处理函数，但是不直接调用，而是将函数指针传递给操作系统（通过RigesterClass）
* 当消息达到时，操作系统通过这个函数指针调用消息处理函数，处理和相应消息。
*
* Windows窗口应用程序是一种消息驱动的程序框架。
* Windows系统中一共有几百种消息，常用的有几十种，如：
*
* WM_CREATE		当窗口被创建是会收到此消息
* WM_PAINT		当窗口应该绘制GDI图形是会收到此消息
* WM_SIZE		当窗口大小变化后会
* WM_MOVE		当窗口被移动后
* WM_DESTROY		当点击窗口的关闭按钮后
* WM_KEYDOWN		当键盘的键被按下以后
* WM_KEYUP		当键盘的键弹起以后
* WN_CHAR		当输入字符以后
* WM_TIMER		当计时器到时以后
* WM_LBUTTONDOWN WM_LBUTTONUP WM_RBUTTONDOWN WM_RBUTTONUP		分别为鼠标左右键按下和弹起
* WM_LBUTTONDBLCLK		鼠标左键双击
* WM_COMMAND		一般在窗口的菜单被点击后
* WN_NOTIFY		一般在子窗口被进行了某项操作时，父窗口会收到此消息，在子窗口是控件的情况下常被使用
* WM_SIZING		当窗口在大小变化的过程中
* WM_MOVING		当窗口在移动过程中
* WM_SETFOCUS	当窗口获得鼠标\键盘焦点
* WM_KILLFOCUS	当窗口失去鼠标\键盘焦点
*
*******************************************************************************/
//add
HBITMAP bmpExercising;

LONG CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	int flag;
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		hpicture0 = LoadImage(NULL, IMAGINE_PAPER,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hpicture[0]= LoadImage(NULL, IMAGINE_DARGON,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hpicture[1] = LoadImage(NULL, IMAGINE_DOG,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hpicture[2] = LoadImage(NULL, IMAGINE_KNIVE,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hpicture[3] =LoadImage(NULL, IMAGINE_HUANG,
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hpicture[4] = LoadImage(NULL, IMAGINE_LIGHT,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		picture = LoadImage(NULL, IMAGINE_HEXIN,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		CreateGame(hwnd);
		ReSizeGameWnd(hwnd);
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		GamePaint(hwnd);
		break;

	case WM_LBUTTONDOWN:
		//返回滑块序号
		nCode[count++] = TransferPos(LOWORD(lParam), HIWORD(lParam));
		if (count == 1)
		{
			Dispatch(nCode[0]);
			GamePaint(hwnd);
		}
		if (count == 2)
		{
			step++;
			count = 0;
			flag=DispatchCode(nCode);
			if(flag==1)
				GamePaint(hwnd);
		}
		if (step > 88)
		{
			MessageBox(0, TEXT("You have run out of all the chances!"), TEXT("Game Over!"), 0);
			ExitProcess(0);
		}
		if (CMAN[2].x == 2 && CMAN[2].y == 4)
		{
			MessageBox(0, TEXT("You have saved the little sweet sucessfully!"), TEXT("Congratulation!"), 0);
			ExitProcess(0);
		}
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;


	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}