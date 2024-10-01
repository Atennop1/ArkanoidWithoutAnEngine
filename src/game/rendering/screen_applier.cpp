#include "screen_applier.hpp"

arkanoid::ScreenApplier::ScreenApplier(const WindowReferences &window_references)
    : window_references_(window_references) { }

void arkanoid::ScreenApplier::Update(float delta)
{
    SDL_RenderPresent(window_references_.Renderer());
}
