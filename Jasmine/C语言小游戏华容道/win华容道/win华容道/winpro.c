// ���õ�ͷ�ļ�
#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include "winlay.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

// ��ͼʱʹ�õı�ʾ�ߺ�ʳ���Բ�ε�ֱ�����ص������
#define CELL_PIXEL			80

// ������ͼ����ɫ
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
* ##########����Windows��������##########
*
* Windows��C���ԵĻ����϶����˺ܶ�Windows���е����͡�����ͨ��C���Թؼ���typedef����ġ�
* Windows���Ͷ���ȫ��д��
*
* DWORD LPSTR WPARAM LPARAM HWND��
* ���У���'H'��ͷ���������Ͷ��Ǿ��
*
*******************************************************************************/

/*******************************************************************************
* ##########   ���ھ��    ##########
*
* �����Windowsϵͳ�еĻ�����������
* �����ϵͳ����ı�ʶ��������Ψһ��ʾһ��ϵͳ����
* ���磺�ļ������ڡ��̡߳���ʱ���ȵȡ�
* ���������Ҳ��ϸ�֣������ľ����HANDLE�����ھ��HWND��GDI��ˢ���HBRUSH�ȡ�
* ������H��ͷ�����ͻ������Ǿ�����͡�
*
*******************************************************************************/

// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;
int nCode[2];
int count = 0;
int step=0;


// ��������
HBITMAP hpicture0;
HBITMAP hpicture[5];
HBITMAP picture;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


/*******************************************************************************
* ##########   ��ں���WinMain    ##########
*
* WindowsӦ�ó������ں�����WinMain���������λ���������Ʊ�׼C���Ե�main����
*
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance, // �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,  // �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)   // ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{

	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = "MainMenu";
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// �����������������Ѿ�ע���˵Ĵ�����
		TEXT("���ݵ�"),		// title-bar string 
		WS_CAPTION | WS_SYSMENU,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);

	mciSendString(TEXT("close Lil'Goldfish.wav"), 0, 0, 0);
	mciSendString(TEXT("play Lil'Goldfish.wav"), NULL, NULL, NULL);

	/*******************************************************************************
	* ##########   MSG���ͺ���Ϣ    ##########
	*
	* Windows����Ӧ�ó�����һ����Ϣ�����ĳ����ܡ�
	* Windows����Ӧ�ó��������Ժ������߳̾�һֱ����
	* "�ȴ���Ϣ--��ȡ��Ϣ--ЧӦ��Ϣ" ��ѭ��֮�У�ֱ�������˳���
	*
	* ��ν��Ϣ��Windowsϵͳ���е�һ��ϵͳ����ͻ��ƣ�
	* �ǲ���ϵͳ��ĳЩϵͳ״̬����ʱ�ӣ����û����������������������ϵͳ�жϽ��з�װ�Ժ�
	* ���Է��͵�Ӧ�ó��򣬲���Ӧ�ó�����д�����û�̬����
	*
	* "MSG"����������ʾ"��Ϣ"���������͡� ���ﶨ����һ��MSG���͵ı�����������Ϊmsg
	*
	*******************************************************************************/


	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
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
	* ##########   ���� GDI    ##########
	*
	* GDI��ȫ����Graphics Device Interface��ͼ���豸�ӿڡ�
	* GDI��Windowsϵͳ���������ͼ��ͼ��ӿڣ�������������ʾ����GDI��������Ĳ��֣�
	* ���Ƕ��ڱ�д̰����������С��Ϸ�Ѿ��㹻���ˡ�
	*
	* ����GDI��������������
	* 1��DC��DC��ȫ����Device Context�����Ʋ����ڴ˽��С�����������Ϊһ�黭������Ӧ��Ļ��һ������
	*      GDI�Ļ��Ʋ���������һ��DC�Ͻ��У���˵�һ�����ǵõ�DC�ľ����BeginPaint����GetDC������
	* 2��GDI���󣺰���PEN��BRUSH��FONT�ȣ�ÿһ�ֻ��Ʋ�������ʹ�õ�һ�����߶��GDI����
	*      ���ԣ��ڻ��Ʋ���֮ǰ�����һ�������ǽ��������õ�GDI�������DC�У�ʹ��SelectObject������ɡ�
	* 3�����Ʋ���������DC��ʹ�ñ�ѡ����DC�е�GDI�������ͼ�Ρ����������ֵȡ�
	*      ��LineTo����������Ellipse����(��)Բ��Rectangle�������Ρ�TextOut�������
	*
	* ʹ��GDI�������ͼ�������ض������̣�����:
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

	// ������Ҫ�õ���PEN��BRUSH
	hpen = CreatePen(PS_NULL, 0, COLOR_BOUNDARY);  // PEN�� PS_NULL��ʾ���ɼ�
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
	* #############  ������  ################
	*
	*******************************************************************************/
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	/*******************************************************************************
	* #############  ��С��  ################
	*
	*******************************************************************************/
	//hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushSolider);
	//hOldPen = (HPEN)SelectObject(hdcmem, hpen);
	//for (i = 0;i < 4;i++)
	//{
	//	soldier[i] = GetSoldier(i);

	//	// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
	//	Rectangle(hdcmem,
	//		soldier[i]->x * CELL_PIXEL + rectBoundary.left,
	//		soldier[i]->y * CELL_PIXEL + rectBoundary.top,
	//		(soldier[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
	//		(soldier[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	//}

	// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
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
	* #############  ����  ################
	*
	*******************************************************************************/
	
	//for (m = 0;m <= 4;m++)
	//{
	//	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushGeneral[m]);
	//	for (i = 0;i < 2;i++)
	//	{
	//		general = GetGeneral(m,i);

	//		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
	* #############  ���ܲ�  ################
	*
	*******************************************************************************/
	//hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushCMAN);
	//for (i = 0;i < 4;i++)
	//{
	//	cman = GetCMAN(i);

	//	// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
	


	//���߿�
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
			{//����
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, (General[m][0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 1)*CELL_PIXEL + rectBoundary.left - 2, (General[m][0].y + 2)*CELL_PIXEL + rectBoundary.top - 2);
				LineTo(hdcmem, (General[m][0].x + 1)*CELL_PIXEL + rectBoundary.left - 2, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
				LineTo(hdcmem, General[m][0].x * CELL_PIXEL + 22, General[m][0].y * CELL_PIXEL + rectBoundary.top + 2);
			}
			else
			{//�Ὣ
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
	* #############  ��ǽ  ################
	*
	*******************************************************************************/

	SelectObject(hdcmem, hPenBoundary);

	// ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	/*******************************************************************************
	* #############  дһ����  ################
	*
	*******************************************************************************/

	// ������һ���������
	hFont = CreateFont(38, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, TEXT("���ȴ��칷 Step %d"), step);
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		// ����ַ�����
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}

	// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	/*******************************************************************************
	* #############  ���պ��ͷ���Դ  ################
	*
	*******************************************************************************/
	// ������Դ
	// DeleteObject �ͷ�GDI����
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
	* #############  ReleaseDC ����  ################
	* �ͷ�ռ�õ�DC��ϵͳ��Դ��
	*******************************************************************************/
	ReleaseDC(hwnd, hdc);
}


/*******************************************************************************
* ##########   ������Ϸ���������ϵ��С������Ϸ���ڴ�С    ##########
*******************************************************************************/

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	Pgame_coord pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left = 20;
	rectBoundary.top = 20;
	rectBoundary.right = 20 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 20 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // ����߽���������߱߿���ȡ�
		rectBoundary.bottom + 120, //��������Ϣ������ʾ�ռ䡣
		TRUE);
}


/*******************************************************************************
* ##########   ��Ϣ����ص�����    ##########
*
* ������ÿ�յ�һ����Ϣ���˺����ͱ�����һ�Ρ�
* ������Ϣ�ĵ��ﲻȷ���ԣ���ˣ���Ϣ�����ĵ����ǻص��ģ�����
* Ӧ�ó��������Ϣ�����������ǲ�ֱ�ӵ��ã����ǽ�����ָ�봫�ݸ�����ϵͳ��ͨ��RigesterClass��
* ����Ϣ�ﵽʱ������ϵͳͨ���������ָ�������Ϣ���������������Ӧ��Ϣ��
*
* Windows����Ӧ�ó�����һ����Ϣ�����ĳ����ܡ�
* Windowsϵͳ��һ���м�������Ϣ�����õ��м�ʮ�֣��磺
*
* WM_CREATE		�����ڱ������ǻ��յ�����Ϣ
* WM_PAINT		������Ӧ�û���GDIͼ���ǻ��յ�����Ϣ
* WM_SIZE		�����ڴ�С�仯���
* WM_MOVE		�����ڱ��ƶ���
* WM_DESTROY		��������ڵĹرհ�ť��
* WM_KEYDOWN		�����̵ļ��������Ժ�
* WM_KEYUP		�����̵ļ������Ժ�
* WN_CHAR		�������ַ��Ժ�
* WM_TIMER		����ʱ����ʱ�Ժ�
* WM_LBUTTONDOWN WM_LBUTTONUP WM_RBUTTONDOWN WM_RBUTTONUP		�ֱ�Ϊ������Ҽ����º͵���
* WM_LBUTTONDBLCLK		������˫��
* WM_COMMAND		һ���ڴ��ڵĲ˵��������
* WN_NOTIFY		һ�����Ӵ��ڱ�������ĳ�����ʱ�������ڻ��յ�����Ϣ�����Ӵ����ǿؼ�������³���ʹ��
* WM_SIZING		�������ڴ�С�仯�Ĺ�����
* WM_MOVING		���������ƶ�������
* WM_SETFOCUS	�����ڻ�����\���̽���
* WM_KILLFOCUS	������ʧȥ���\���̽���
*
*******************************************************************************/
//add
HBITMAP bmpExercising;

LONG CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	int flag;
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
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

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT:
		GamePaint(hwnd);
		break;

	case WM_LBUTTONDOWN:
		//���ػ������
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