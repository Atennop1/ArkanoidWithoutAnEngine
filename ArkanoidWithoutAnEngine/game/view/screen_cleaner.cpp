#include "screen_cleaner.h"
#include "render_packs.h"
#include "../shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
ScreenCleaner::ScreenCleaner(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void ScreenCleaner::Update(float delta)
{
    RECT rect;
    if (GetWindowRect(*m_window_handles_->HWND(), &rect))
    {
        Shortcuts::SelectRenderPack(*m_window_handles_->HDC(), RenderPacks::kBlackRenderPack);
        Rectangle(*m_window_handles_->HDC(), rect.left, rect.top, rect.right, rect.bottom);
    }
}

//----------------------------------------------------------------------------------------------------
