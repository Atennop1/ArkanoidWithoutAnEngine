#include "Application.h"

#include "winuser.h"
#include "../../resource.h"
#include "../../Game/Game.h"
#include "../../Game/View/VisualizationConsts.h"

Application::Application(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR lpCmdLine, int cmdShow)
    : m_sizeTitle { }, m_sizeWindowClass { }
{
    m_instance = instance;
    m_previousInstance = previousInstance;
    m_lpCmdLine = lpCmdLine;
    m_cmdShow = cmdShow;

    Game = nullptr;
    CurrentHDC = nullptr;
}

BOOL Application::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    RECT windowRect;
    
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = 320 * SCALE_MULTIPLIER;
    windowRect.bottom = 200 * SCALE_MULTIPLIER;
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, TRUE);

    HWND hWnd = CreateWindowW(m_sizeWindowClass, m_sizeTitle, WS_OVERLAPPEDWINDOW,
       0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, this);

    if (!hWnd)
        return FALSE;

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)(void*)this);
    Game = new ::Game(new WindowHandles(&CurrentHDC, &hWnd));
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

ATOM Application::RegisterWindow(HINSTANCE hInstance) const
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc    = ProceedWindow;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    wcex.lpszClassName  = m_sizeWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

LRESULT Application::ProceedWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Application *application = nullptr;
    const long userData = GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (userData != 0)
    {
        const auto ptr = (void*)userData;
        application = (Application*)ptr;
    }

    switch (message)
    {
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
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
            application->CurrentHDC = BeginPaint(hWnd, &ps);
            
            application->Game->Render(application->CurrentHDC);
            EndPaint(hWnd, &ps);
        }
        break;
    
    case WM_DESTROY:
        free(application);
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        {
            const KeyType keyType = Converters::FromWParam(wParam);

            if (keyType != KT_None)
                application->Game->OnKeyDown(keyType);
        
            break;
        }
        
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return 0;
}

MSG Application::Run()
{
    UNREFERENCED_PARAMETER(m_previousInstance);
    UNREFERENCED_PARAMETER(m_lpCmdLine);

    LoadStringW(m_instance, IDS_APP_TITLE, m_sizeTitle, 100);
    LoadStringW(m_instance, IDC_ARKANOIDWITHOUTANENGINE, m_sizeWindowClass, 100);
    
    RegisterWindow(m_instance);
    InitInstance(m_instance, m_cmdShow);

    MSG message;
    const HACCEL hAccelTable = LoadAccelerators(m_instance, MAKEINTRESOURCE(IDC_ARKANOIDWITHOUTANENGINE));

    while (GetMessage(&message, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(message.hwnd, hAccelTable, &message))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return message;
}

