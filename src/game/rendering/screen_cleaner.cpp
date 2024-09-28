#include "screen_cleaner.hpp"
#include "../shortcuts/render_colors.hpp"
#include "../shortcuts/shortcuts.hpp"

arkanoid::ScreenCleaner::ScreenCleaner(const WindowReferences &window_reference)
    : m_window_references_(window_reference) { }

void arkanoid::ScreenCleaner::Update(float delta)
{
    Shortcuts::SelectColor(m_window_references_.Renderer(), RenderColors::m_k_black_color_);
    SDL_RenderClear(m_window_references_.Renderer());
}
