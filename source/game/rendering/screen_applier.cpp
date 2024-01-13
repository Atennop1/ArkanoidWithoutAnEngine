#include "screen_applier.h"

ScreenApplier::ScreenApplier(const WindowReferences &window_references)
    : m_window_references_(const_cast<WindowReferences&>(window_references)) { }

void ScreenApplier::Update(float delta)
{
    SDL_RenderPresent(m_window_references_.Renderer());
}
