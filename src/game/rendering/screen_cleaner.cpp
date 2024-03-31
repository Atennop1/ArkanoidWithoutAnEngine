#include "screen_cleaner.hpp"
#include "../shortcuts/render_colors.hpp"
#include "../shortcuts/shortcuts.hpp"

ScreenCleaner::ScreenCleaner(const std::shared_ptr<WindowReferences> &window_reference)
    : m_window_references_(window_reference) { }

void ScreenCleaner::Update(float delta)
{
    Shortcuts::SelectColor(m_window_references_->Renderer(), RenderColors::kBlackColor);
    SDL_RenderClear(m_window_references_->Renderer());
}
