#include "application.h"
#include "../../core/includes/resource.h"
#include "../../Game/game.h"
#include "../../Game/View/visualization_consts.h"

//----------------------------------------------------------------------------------------------------
LRESULT StaticProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter)
{
    if (message == WM_NCCREATE)
    {
        const auto long_param_create_struct = reinterpret_cast<LPCREATESTRUCT>(long_parameter);
        auto* application = static_cast<Application*>(long_param_create_struct->lpCreateParams);
        
        SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LPARAM>(application));
        return TRUE;
    }

    const auto* application = reinterpret_cast<Application*>(GetWindowLongPtr(window, GWLP_USERDATA));
    return application->ProcessWindow(window, message, word_parameter, long_parameter);
}

//----------------------------------------------------------------------------------------------------
Application::Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
    : m_title_buffer_size_(), m_window_buffer_size_(), m_game_(nullptr), m_current_hdc_(nullptr)
{
    m_instance_ = instance;
    m_previous_instance_ = previous_instance;

    m_command_line_ = command_line;
    m_window_showing_type_ = window_showing_type;

    UNREFERENCED_PARAMETER(m_previous_instance_);
    UNREFERENCED_PARAMETER(m_command_line_);

    LoadStringW(m_instance_, IDS_APP_TITLE, m_title_buffer_size_, 100);
    LoadStringW(m_instance_, IDC_ARKANOIDWITHOUTANENGINE, m_window_buffer_size_, 100);
}

//----------------------------------------------------------------------------------------------------
BOOL Application::InitInstance(HINSTANCE instance, int window_showing_type)
{
    RECT window_rectangle;
    
    window_rectangle.left = 0;
    window_rectangle.top = 0;
    window_rectangle.right = 320 * kScaleMultiplier;
    window_rectangle.bottom = 200 * kScaleMultiplier;
    AdjustWindowRect(&window_rectangle, WS_OVERLAPPEDWINDOW, TRUE);

    auto window = CreateWindowW(m_window_buffer_size_, m_title_buffer_size_, WS_OVERLAPPEDWINDOW,
       0, 0, window_rectangle.right - window_rectangle.left, window_rectangle.bottom - window_rectangle.top, NULL, NULL, instance, this);

    if (!window)
        return FALSE;

    char buffer[320 * 6][200 * 6][3];
    BITMAPINFO bitmap_info = { };
    
    bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.bmiHeader.biWidth = window_rectangle.bottom;
    bitmap_info.bmiHeader.biHeight = -window_rectangle.right;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

    const HDC desktop_dc = GetDC(window);
    const HBITMAP independent_bitmap = CreateDIBSection(desktop_dc, &bitmap_info, DIB_RGB_COLORS, (void**)&buffer, nullptr, 0);
    const HDC independent_bitmap_dc = CreateCompatibleDC(desktop_dc);
    SelectObject(independent_bitmap_dc, independent_bitmap);

    m_current_hdc_ = desktop_dc;
    m_game_ = new Game(new WindowHandles(&m_current_hdc_, &window));
    
    ShowWindow(window, window_showing_type);
    UpdateWindow(window);
    return TRUE;
}

//----------------------------------------------------------------------------------------------------
ATOM Application::RegisterWindow(HINSTANCE instance) const
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance;
    wcex.lpszClassName = m_window_buffer_size_;
    
    wcex.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_ARKANOIDWITHOUTANENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ARKANOIDWITHOUTANENGINE);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpfnWndProc = StaticProcessWindow;
    return RegisterClassExW(&wcex);
}

//----------------------------------------------------------------------------------------------------
LRESULT CALLBACK Application::ProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const
{
    switch (message)
    {
    case WM_COMMAND:
        {
            switch (LOWORD(word_parameter))
            {
            case IDM_EXIT:
                DestroyWindow(window);
                break;
                    
            default:
                return DefWindowProc(window, message, word_parameter, long_parameter);
            }
        }
        break;
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BitBlt(BeginPaint(window, &ps), 0, 0, 320 * kScaleMultiplier, 200 * kScaleMultiplier, m_current_hdc_, 0, 0, SRCCOPY);
            EndPaint(window, &ps);
        }
        break;
    
    case WM_DESTROY:
        free(m_game_);
        PostQuitMessage(0);
        break;

    case WM_QUIT:
        free(m_game_);
        break;
        
    default:
        return DefWindowProc(window, message, word_parameter, long_parameter);
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------------
MSG Application::Activate()
{
    RegisterWindow(m_instance_);
    InitInstance(m_instance_, m_window_showing_type_);
    
    m_game_->Activate();
    return { };
}

//----------------------------------------------------------------------------------------------------
