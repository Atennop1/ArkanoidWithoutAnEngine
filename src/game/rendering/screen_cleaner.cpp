#include "screen_cleaner.hpp"
#include "../shortcuts/render_colors.hpp"
#include "../shortcuts/shortcuts.hpp"

arkanoid::ScreenCleaner::ScreenCleaner(const WindowReferences &window_reference)
    : window_references_(window_reference) { }

void arkanoid::ScreenCleaner::Update(float delta)
{
    Shortcuts::SelectColor(window_references_.Renderer(), RenderColors::kBlackColor);
    SDL_RenderClear(window_references_.Renderer());
}
