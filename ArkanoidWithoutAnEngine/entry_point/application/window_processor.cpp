#include "window_processor.h"
#include "application.h"
#include "../../core/includes/resource.h"
#include "../../game/rendering/rendering_consts.h"

//----------------------------------------------------------------------------------------------------
LRESULT StaticProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter)
{
    if (message == WM_NCCREATE)
    {
        const auto long_param_create_struct = reinterpret_cast<LPCREATESTRUCT>(long_parameter);
        auto* window_processor = static_cast<WindowProcessor*>(long_param_create_struct->lpCreateParams);
        
        SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LPARAM>(window_processor));
        return TRUE;
    }

    const auto window_processor = reinterpret_cast<WindowProcessor*>(GetWindowLongPtr(window, GWLP_USERDATA));
    return window_processor->ProcessWindow(window, message, word_parameter, long_parameter);
}

WindowProcessor::WindowProcessor(Game* game, WindowHandles* window_handles, HDC* initial_hdc)
{
    m_game_ = game;
    m_window_handles_ = window_handles;
    m_initial_hdc_ = initial_hdc;
}

//----------------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProcessor::ProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const
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
            BitBlt(BeginPaint(window, &ps), 0, 0, kWindowWidth, kWindowHeight, *m_window_handles_->HDC(), 0, 0, SRCCOPY);
            EndPaint(window, &ps);
        }
        break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_QUIT:
        free(m_game_);
        DeleteDC(*m_window_handles_->HDC());
        ReleaseDC(window, *m_initial_hdc_);
        break;
        
    default:
        return DefWindowProc(window, message, word_parameter, long_parameter);
    }
    
    return 0;
}
