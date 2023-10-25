#include "screen_applier.h"
#include "rendering_consts.h"

//----------------------------------------------------------------------------------------------------
ScreenApplier::ScreenApplier(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void ScreenApplier::Update(float delta)
{
    const auto window = *m_window_handles_->HWND();
    const auto hdc = GetDC(window);
    
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, *m_window_handles_->HDC(), 0, 0, SRCCOPY);
    ReleaseDC(window, hdc);
}

//----------------------------------------------------------------------------------------------------