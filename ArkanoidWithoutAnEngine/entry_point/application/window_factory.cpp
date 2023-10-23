#include "window_factory.h"
#include "window_processor.h"
#include "../../game/rendering/rendering_consts.h"
#include "../../core/includes/resource.h"

void WindowFactory::RegisterWindow() const
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_instance_;
    wcex.lpszClassName = m_window_buffer_size_;
    
    wcex.hIcon = LoadIcon(m_instance_, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpfnWndProc = StaticProcessWindow;
    RegisterClassExW(&wcex);
}

HWND WindowFactory::CreateWindowInstance()
{
    RECT window_rectangle;
    
    window_rectangle.left = 0;
    window_rectangle.top = 0;
    window_rectangle.right = kWindowWidth;
    window_rectangle.bottom = kWindowHeight;
    AdjustWindowRect(&window_rectangle, WS_OVERLAPPEDWINDOW, TRUE);

    const auto window  = CreateWindowW(m_window_buffer_size_, m_title_buffer_size_, WS_OVERLAPPEDWINDOW,
       0, 0, window_rectangle.right - window_rectangle.left, window_rectangle.bottom - window_rectangle.top, NULL, NULL, m_instance_, this);

    if (!window)
        return nullptr;
    
    ShowWindow(window, m_window_showing_type_);
    UpdateWindow(window);
    return window;
}

WindowFactory::WindowFactory(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
{
    m_instance_ = instance;
    m_window_showing_type_ = window_showing_type;

    UNREFERENCED_PARAMETER(previous_instance);
    UNREFERENCED_PARAMETER(command_line);

    LoadStringW(m_instance_, IDS_APP_TITLE, m_title_buffer_size_, 100);
    LoadStringW(m_instance_, IDC_ARKANOIDWITHOUTANENGINE, m_window_buffer_size_, 100);
}

HWND WindowFactory::Create()
{
    RegisterWindow();
    return CreateWindowInstance();
}
