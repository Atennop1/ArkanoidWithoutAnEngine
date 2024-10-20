#include "game/rendering/screen_applier.hpp"

namespace arkanoid
{
ScreenApplier::ScreenApplier(const WindowReferences &window_references)
    : window_references_(window_references) {}

void ScreenApplier::Update(float delta)
{
    SDL_RenderPresent(window_references_.Renderer());
}
}
