#include "screen_applier.h"
#include "visualization_consts.h"

//----------------------------------------------------------------------------------------------------
ScreenApplier::ScreenApplier(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void ScreenApplier::Update(float delta)
{
    const auto hdc = GetDC(*m_window_handles_->HWND());
    BitBlt(hdc, 0, 0, kWindowWidth, kWindowHeight, *m_window_handles_->HDC(), 0, 0, SRCCOPY);
    ReleaseDC(*m_window_handles_->HWND(), hdc);
}

//----------------------------------------------------------------------------------------------------