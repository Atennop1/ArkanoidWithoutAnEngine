#include "screen_cleaner.h"
#include "../shortcuts/render_colors.h"
#include "../shortcuts/shortcuts.h"

ScreenCleaner::ScreenCleaner(const WindowReferences &window_reference)
    : m_window_references_(const_cast<WindowReferences&>(window_reference)) { }

void ScreenCleaner::Update(float delta)
{
    Shortcuts::SelectColor(m_window_references_.Renderer(), RenderColors::kBlackColor);
    SDL_RenderClear(m_window_references_.Renderer());
}
