#include "Application.h"
#include "../../resource.h"
#include "../../Game/Game.h"
#include "../../Game/View/VisualizationConsts.h"

//----------------------------------------------------------------------------------------------------
LRESULT StaticProcessWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_NCCREATE)
    {
        const auto lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        auto* application = static_cast<Application*>(lpcs->lpCreateParams);
        
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(application));
        return TRUE;
    }

    auto* application = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return application->ProcessWindow(hWnd, message, wParam, lParam);
}

//----------------------------------------------------------------------------------------------------
Application::Application(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR lpCmdLine, int cmdShow)
    : m_sizeTitle(), m_sizeWindowClass()
{
    m_instance = instance;
    m_previousInstance = previousInstance;
    m_lpCmdLine = lpCmdLine;
    m_cmdShow = cmdShow;
    
    m_currentHDC = nullptr;
    m_game = nullptr;
}

//----------------------------------------------------------------------------------------------------
BOOL Application::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    RECT windowRect;
    
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = 320 * SCALE_MULTIPLIER;
    windowRect.bottom = 200 * SCALE_MULTIPLIER;
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, TRUE);

    HWND hWnd = CreateWindowW(m_sizeWindowClass, m_sizeTitle, WS_OVERLAPPEDWINDOW,
       0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, this);

    if (!hWnd)
        return FALSE;

    m_game = new Game(new WindowHandles(&m_currentHDC, &hWnd));
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

//----------------------------------------------------------------------------------------------------
ATOM Application::RegisterWindow(HINSTANCE hInstance) const
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = m_sizeWindowClass;
    
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpfnWndProc = StaticProcessWindow;
    return RegisterClassExW(&wcex);
}

//----------------------------------------------------------------------------------------------------
LRESULT CALLBACK Application::ProcessWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
            m_currentHDC = BeginPaint(hWnd, &ps);

            m_game->Render(m_currentHDC);
            EndPaint(hWnd, &ps);
        }
        break;
    
    case WM_DESTROY:
        free(m_game);
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        {
            const KeyType keyType = Converters::FromWParam(wParam);

            if (keyType != KT_None)
                m_game->OnKeyDown(keyType);
        
            break;
        }
        
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------
