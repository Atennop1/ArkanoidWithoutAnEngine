// ArkanoidWithoutAnEngine.cpp : Defines the entry point for the application.

#include "framework.h"
#include "ArkanoidWithoutAnEngine.h"

#define MAX_LOADSTRING 100
#define SCALE_MULTIPLIER 6

#define BRICK_WIDTH 15
#define BRICK_HEIGHT 7

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
 
//----------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ARKANOIDWITHOUTANENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    MSG message;
    const HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ARKANOIDWITHOUTANENGINE));

    while (GetMessage(&message, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(message.hwnd, hAccelTable, &message))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return (int)message.wParam;
}

//----------------------------------------------------------------------------------------------------
void DrawBrick(HDC hdc, COLORREF color, int x, int y)
{
    const HPEN pen = CreatePen(PS_SOLID, 0, color);
    const HBRUSH brush = CreateSolidBrush(color);

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 10, 10);
}

//----------------------------------------------------------------------------------------------------
void DrawFrame(HDC hdc)
{
    constexpr COLORREF violet = RGB(255, 85, 255);
    constexpr COLORREF blue = RGB(85, 255, 255);

    DrawBrick(hdc, violet, 8, 6);
    DrawBrick(hdc, blue, 8, 6 + (BRICK_HEIGHT + 1));

    DrawBrick(hdc, blue, 8 + (BRICK_WIDTH + 1), 6);
    DrawBrick(hdc, violet, 8 + (BRICK_WIDTH + 1), 6 + (BRICK_HEIGHT + 1));
}

//----------------------------------------------------------------------------------------------------
//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//----------------------------------------------------------------------------------------------------
//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   RECT windowRect;

   windowRect.left = 0;
   windowRect.top = 0;
   windowRect.right = 320 * SCALE_MULTIPLIER;
   windowRect.bottom = 200 * SCALE_MULTIPLIER;
   AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, TRUE);

   const HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//----------------------------------------------------------------------------------------------------
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
            {
                switch (LOWORD(wParam))
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
            }
            break;
        
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                DrawFrame(BeginPaint(hWnd, &ps));
                EndPaint(hWnd, &ps);
            }
            break;
    
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------------
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
                {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;
        
        default:;
    }
    
    return FALSE;
}
//----------------------------------------------------------------------------------------------------
