#include "window_updater.h"
#include "../../../core/includes/resource.h"
#include "../../../game/rendering/rendering_consts.h"

//----------------------------------------------------------------------------------------------------
LRESULT UpdateApplication(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter)
{
    if (message == WM_NCCREATE)
    {
        const auto long_param_create_struct = reinterpret_cast<LPCREATESTRUCT>(long_parameter);
        auto window_updater = static_cast<WindowUpdater*>(long_param_create_struct->lpCreateParams);

        SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LPARAM>(window_updater));
        return TRUE;
    }

    const auto window_updater = reinterpret_cast<WindowUpdater*>(GetWindowLongPtr(window, GWLP_USERDATA));
    return window_updater->Update(window, message, word_parameter, long_parameter);
}

//----------------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowUpdater::Update(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const
{
    if (message == WM_COMMAND && LOWORD(word_parameter) == IDM_EXIT)
    {
        DestroyWindow(window);
        return 0;
    }

    if (message == WM_PAINT)
    {
        PAINTSTRUCT ps;
        BitBlt(BeginPaint(window, &ps), 0, 0, kWindowWidth, kWindowHeight, *m_window_handles_->HDC(), 0, 0, SRCCOPY);
        
        EndPaint(window, &ps);
        return 0;
    }
    
    return DefWindowProc(window, message, word_parameter, long_parameter);
}

//----------------------------------------------------------------------------------------------------
WindowUpdater::WindowUpdater(WindowHandles* window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
WindowUpdater::~WindowUpdater()
{
    free(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------