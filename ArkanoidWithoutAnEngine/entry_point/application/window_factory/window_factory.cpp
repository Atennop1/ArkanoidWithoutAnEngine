#include "window_factory.h"

#include <cwchar>
#include "../window_updater/window_updater.h"
#include "../../../game/rendering/rendering_constants.h"
#include "../../../core/includes/resource.h"

//----------------------------------------------------------------------------------------------------
void WindowFactory::RegisterWindow() const
{
    WNDCLASSEXW window_class;
    window_class.cbSize = sizeof(WNDCLASSEX);

    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = m_instance_;
    window_class.lpszClassName = m_window_buffer_size_;
    
    window_class.hIcon = LoadIcon(m_instance_, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
    window_class.lpszMenuName = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.hIconSm = LoadIcon(window_class.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    window_class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    window_class.lpfnWndProc = UpdateApplication;
    RegisterClassExW(&window_class);
}

//----------------------------------------------------------------------------------------------------
HWND WindowFactory::CreateWindowInstance() const
{
    RECT window_rectangle;
    
    window_rectangle.left = 0;
    window_rectangle.top = 0;
    window_rectangle.right = RenderingConstants::kWindowWidth;
    window_rectangle.bottom = RenderingConstants::kWindowHeight;
    AdjustWindowRect(&window_rectangle, WS_OVERLAPPEDWINDOW, TRUE);

    const auto window = CreateWindowW(m_window_buffer_size_, m_title_buffer_size_, WS_OVERLAPPEDWINDOW, 0, 0, window_rectangle.right - window_rectangle.left, window_rectangle.bottom - window_rectangle.top, NULL, NULL, m_instance_, m_window_updater_);

    if (!window)
        return nullptr;
    
    ShowWindow(window, m_window_showing_type_);
    UpdateWindow(window);
    return window;
}

//----------------------------------------------------------------------------------------------------
WindowFactory::WindowFactory(WindowUpdater* window_updater, HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
{
    m_instance_ = instance;
    m_window_showing_type_ = window_showing_type;
    m_window_updater_ = window_updater;

    UNREFERENCED_PARAMETER(previous_instance);
    UNREFERENCED_PARAMETER(command_line);

    LoadStringW(m_instance_, IDS_APP_TITLE, m_title_buffer_size_, std::wcslen(m_title_buffer_size_));
    LoadStringW(m_instance_, IDC_ARKANOIDWITHOUTANENGINE, m_window_buffer_size_, std::wcslen(m_window_buffer_size_));
}

//----------------------------------------------------------------------------------------------------
HWND WindowFactory::Create() const
{
    RegisterWindow();
    return CreateWindowInstance();
}

//----------------------------------------------------------------------------------------------------
