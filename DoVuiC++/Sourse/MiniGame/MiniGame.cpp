// MiniGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MiniGame.h"
#include <commctrl.h>
#include <windowsx.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const int BUFFER_SIZE = 10240;
WCHAR g_buffer[BUFFER_SIZE];
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK Dialog1_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Dialog2_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MINIGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIGAME));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINIGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 400, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

HFONT hFont;

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HWND Start = CreateWindowEx(NULL, L"BUTTON", L"Start" ,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 180, 150, 60, hwnd,
		(HMENU)IDC_Start, lpCreateStruct->hInstance, NULL);
	SetWindowFont(Start, hFont, TRUE);

	HWND HuongDan = CreateWindowEx(NULL, L"BUTTON", L"Hướng Dẫn",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 250, 150, 60, hwnd,
		(HMENU)IDC_HuongDan, lpCreateStruct->hInstance, NULL);
	SetWindowFont(HuongDan, hFont, TRUE);

	return TRUE;
}

LPCWSTR image[] = { L"Anh.bmp", L"Ao.bmp", L"My.bmp", L"Argentina.bmp", L"Canada.bmp",
						L"DanMach.bmp", L"Duc.bmp", L"Phap.bmp", L"ThuySi.bmp", L"VietNam.bmp" };

LPCWSTR DADung[] = { L"Anh", L"Ao", L"My", L"Argentina", L"Canada",
						L"DanMach", L"Duc", L"Phap", L"ThuySi", L"VietNam" };

LPCWSTR DA1[] = { L"Anh", L"Ao", L"My", L"Canada", L"Canada",
						L"VietNam", L"Duc", L"Anh", L"Canada", L"My" };

LPCWSTR DA2[] = { L"Duc", L"Argentina", L"Argentinay", L"Argentina", L"Anh",
						L"DanMach", L"Anh", L"Phap", L"ThuySi", L"VietNam" };

Random ra;
int index;
int result;
int flag[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int countImage = 0;
int diem = 0;


void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_HuongDan:
		//MessageBox(0, 0, 0, 0);
		result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1),
			hwnd, Dialog1_WndProc);
		ShowWindow(hwnd, SW_SHOW);
		break;
	case IDC_Start:
		result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2),
			hwnd, Dialog2_WndProc);
		ShowWindow(hwnd, SW_SHOW);
		break;
	}
	
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}


INT_PTR CALLBACK Dialog1_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		HFONT hFont;
		HWND HuongDan;
		LOGFONT lf;

	case WM_INITDIALOG:
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);
		HuongDan = CreateWindowEx(NULL, L"STATIC", L"- Đây là mini game kiểm tra kiến thức về sự hiểu biết quốc kì các quốc gia trên thế giới.\n- Chọn tên nước ứng với hình quốc kì.\n- Mỗi câu trả lời đúng được 1 điểm.\n- Good Luck For You.", WS_CHILD | WS_VISIBLE | SS_LEFT,
			20, 20, 500, 200, hDlg,
			(HMENU)IDC_HuongDan, NULL, NULL);
		SetWindowFont(HuongDan, hFont, TRUE);
		ShowWindow(hDlg, SW_SHOW);

	case WM_COMMAND:
		int id = LOWORD(wParam);
		switch (id) {
		case IDC_OK:
			EndDialog(hDlg, TRUE);
			return (INT_PTR)TRUE;
			break;
		case IDC_CLOSE:
			EndDialog(hDlg, FALSE);
			return (INT_PTR)TRUE;
			break;
		}
	}
	return (INT_PTR)FALSE;
}



HWND _static;
HWND answer1;
HWND answer2;
HWND hienThiDiem;
HWND soCauHoi;
WCHAR buffer[256];

INT_PTR CALLBACK Dialog2_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	HANDLE _image;

	switch (message)
	{
	case WM_INITDIALOG:
		_static = CreateWindowEx(WS_EX_STATICEDGE, L"STATIC", NULL,
			WS_CHILD | WS_VISIBLE | SS_BITMAP, 95, 40, 0, 0, hDlg, 0, hInst, NULL);

		index = ra.Next(10);
		flag[index] = 1;
		countImage++;

		_image = LoadImage(hInst, image[index], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessage(_static, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)_image);

		answer1 = CreateWindowEx(NULL, L"BUTTON", DA1[index],
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON , 120, 250, 150, 60, hDlg,
			(HMENU)IDC_Answer1, NULL, NULL);
		//SetWindowFont(answer1, hFont, TRUE);

		answer2 = CreateWindowEx(NULL, L"BUTTON", DA2[index],
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 320, 250, 150, 60, hDlg,
			(HMENU)IDC_Answer2, NULL, NULL);
		//SetWindowFont(answer2, hFont, TRUE);

		hienThiDiem = CreateWindowEx(NULL, L"BUTTON", L"Điểm: 0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 510, 5, 80, 40, hDlg,
			(HMENU)IDC_Answer1, NULL, NULL);
		SetWindowFont(hienThiDiem, hFont, TRUE);

		soCauHoi = CreateWindowEx(NULL, L"BUTTON", L"Câu: 1/10",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 510, 45, 80, 40, hDlg,
			(HMENU)IDC_Answer2, NULL, NULL);
		SetWindowFont(soCauHoi, hFont, TRUE);

		//// Display data stored from global buffer
		//SetDlgItemText(hDlg, IDC_EDIT1, g_buffer);
		//return (INT_PTR)TRUE;

	case WM_COMMAND:
		int id = LOWORD(wParam);
		switch (id) {
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return (INT_PTR)TRUE;
			break;

		case IDC_Answer1:

			if (countImage < 10) {
				wsprintf(buffer, L"Câu: %d/10", countImage + 1);
				SetWindowText(soCauHoi, buffer);
			}

			//kiem tra dap an
			if (DA1[index] == DADung[index]) {
				diem++;
			}

			wsprintf(buffer, L"Điểm: %d", diem);
			SetWindowText(hienThiDiem, buffer);


			if (10 == countImage) {
				//reset choi lai
				int luuDiem = diem;
				countImage = 0;
				diem = 0;
				for (int i = 0; i < 10; i++) {
					flag[i] = 0;
				}


				wsprintf(buffer, L"Bạn trả lời đúng: %d/10 câu", luuDiem);
				MessageBox(0, buffer, L"Score", 0);
				EndDialog(hDlg, FALSE);
				return (INT_PTR)TRUE;

				CloseWindow(hDlg);
				break;
			}

			while (1 == flag[index]) {
				index = ra.Next(10);
			}

			flag[index] = 1;
			countImage++;
			_image = LoadImage(hInst, image[index], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessage(_static, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)_image);
			SetWindowText(answer1, DA1[index]);
			SetWindowText(answer2, DA2[index]);

			ShowWindow(hDlg, SW_SHOW);
			
			break;

		case IDC_Answer2:
			if (countImage < 10) {
				wsprintf(buffer, L"Câu: %d/10", countImage + 1);
				SetWindowText(soCauHoi, buffer);
			}

			//kiem tra dap an
			if (DA2[index] == DADung[index]) {
				diem++;
			}

			wsprintf(buffer, L"Điểm: %d", diem);
			SetWindowText(hienThiDiem, buffer);

			if (10 == countImage) {
				//reset choi lai
				int luuDiem = diem;
				countImage = 0;
				diem = 0;
				for (int i = 0; i < 10; i++) {
					flag[i] = 0;
				}

				wsprintf(buffer, L"Bạn trả lời đúng: %d/10 câu", luuDiem);
				MessageBox(0, buffer, L"Score", 0);
				EndDialog(hDlg, FALSE);
				return (INT_PTR)TRUE;
				CloseWindow(hDlg);
				break;
			}

			while (1 == flag[index]) {
				index = ra.Next(10);
			}

			flag[index] = 1;
			countImage++;
			_image = LoadImage(hInst, image[index], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessage(_static, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)_image);
			SetWindowText(answer1, DA1[index]);
			SetWindowText(answer2, DA2[index]);

			ShowWindow(hDlg, SW_SHOW);

			break;
		}
	}
	return (INT_PTR)FALSE;
}