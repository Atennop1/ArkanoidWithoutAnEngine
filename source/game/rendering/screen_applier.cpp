#include <stdexcept>
#include "screen_applier.h"

//----------------------------------------------------------------------------------------------------
ScreenApplier::ScreenApplier(WindowReferences *window_references)
{
    m_window_references_ = window_references;
}

//----------------------------------------------------------------------------------------------------
void ScreenApplier::Update(float delta)
{
    SDL_RenderPresent(m_window_references_->Renderer());
}

//----------------------------------------------------------------------------------------------------