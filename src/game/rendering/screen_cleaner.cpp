﻿#include "game/rendering/screen_cleaner.hpp"
#include "game/shortcuts/shortcuts.hpp"
#include "game/shortcuts/render_colors.hpp"

namespace arkanoid
{
ScreenCleaner::ScreenCleaner(const WindowReferences &window_reference)
    : window_references_(window_reference) {}

void ScreenCleaner::Update(float delta)
{
    Shortcuts::SelectColor(window_references_.Renderer(), RenderColors::kBlackColor);
    SDL_RenderClear(window_references_.Renderer());
}
}
