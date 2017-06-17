// renderer.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "WinMain.h"
#include "Render/Render.h"

#define MAX_LOADSTRING 100
#include <scoped_allocator>

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

static HWND gWnd;
static HDC hdcScreen = NULL;			// ���׵� HDC
static HBITMAP hbScreen = NULL;			// DIB
static HBITMAP hbOldScreen = NULL;		// �ϵ� BITMAP
unsigned char *fbScreen = NULL;			// frame buffer

float lastMousePosX;
float lastMousePosY;

Renderer* renderer;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	// test log
	printf("test log");

	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RENDERER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RENDERER));

	renderer = new Renderer(fbScreen);

	// ����Ϣѭ��: 
	for (;;)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}			
		}
		
		// todo: render loop
		renderer->Loop();

		HDC hDC = GetDC(gWnd);
		BitBlt(hDC, 0, 0, 800, 600, hdcScreen, 0, 0, SRCCOPY);
		ReleaseDC(gWnd, hDC);
	}
	

	delete renderer;
	FreeConsole();

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RENDERER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RENDERER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HDC hDC;
   BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), 800, -600, 1, 32, BI_RGB,
	   800 * 600 * 4, 0, 0, 0, 0 } };
   RECT rect = { 0, 0, 800, 600 };
   int wx, wy, sx, sy;
   LPVOID ptr;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   gWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!gWnd)
   {
      return FALSE;
   }

   hDC = GetDC(gWnd);
   hdcScreen = CreateCompatibleDC(hDC);
   ReleaseDC(gWnd, hDC);

   hbScreen = CreateDIBSection(hdcScreen, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
   if (hbScreen == NULL) return FALSE;

   hbOldScreen = (HBITMAP)SelectObject(hdcScreen, hbScreen);
   fbScreen = (unsigned char*)ptr;

   AdjustWindowRect(&rect, GetWindowLong(gWnd, GWL_STYLE), 0);
   wx = rect.right - rect.left;
   wy = rect.bottom - rect.top;
   sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
   sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
   if (sy < 0) sy = 0;
   SetWindowPos(gWnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
   SetForegroundWindow(gWnd);

   ShowWindow(gWnd, nCmdShow);
   UpdateWindow(gWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_LEFT:
			renderer->Strafe(-0.05);
			break;
		case VK_RIGHT:
			renderer->Strafe(0.05);
			break;
		case VK_UP:
			renderer->Walk(0.05);
			break;
		case VK_DOWN:
			renderer->Walk(-0.05);
			break;
		}
		break;		
	case  WM_RBUTTONDOWN:
		lastMousePosX = GET_X_LPARAM(lParam);
		lastMousePosY = GET_Y_LPARAM(lParam);
		SetCapture(gWnd);
		break;
	case  WM_RBUTTONUP:
		//Release the capture on the mouse
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		switch (wParam)
		{
		case VK_RBUTTON:

			float xPos = GET_X_LPARAM(lParam);
			float yPos = GET_Y_LPARAM(lParam);
			
			float dx = Deg2Rad(0.25*(xPos - lastMousePosX));
//			float dy = Deg2Rad(0.25*(yPos - lastMousePosY));
//			renderer->Pitch(dy);
			renderer->RotateY(dx);

			lastMousePosX = xPos;
			lastMousePosY = yPos;
			break;
		}		
		break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
