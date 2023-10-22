#include "screen_cleaner.h"
#include "render_packs.h"
#include "visualization_consts.h"
#include "../shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
ScreenCleaner::ScreenCleaner(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void ScreenCleaner::Update(float delta)
{
    const HDC hdc = *m_window_handles_->HDC();
    
    Shortcuts::SelectRenderPack(hdc, RenderPacks::kBlackRenderPack);
    Rectangle(hdc, 0, 0, kWindowWidth, kWindowHeight);
}

//----------------------------------------------------------------------------------------------------
