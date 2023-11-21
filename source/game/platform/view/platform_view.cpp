#include <iostream>
#include "platform_view.h"
#include "../../rendering/rendering_constants.h"
#include "../../Shortcuts/shortcuts.h"
#include "SDL_image.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowReferences *window_references)
{
    m_window_handles_ = window_references;
    m_displaying_rect_ = { 0, 0, 0, 0 };
    m_platform_texture_ = IMG_LoadTexture(m_window_handles_->Renderer(), "assets/sprites/platform.png");
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(Vector2 position)
{
    SDL_QueryTexture(m_platform_texture_, nullptr, nullptr, &m_displaying_rect_.w, &m_displaying_rect_.h);

    m_displaying_rect_.h = m_displaying_rect_.h * RenderingConstants::kScaleMultiplier;
    m_displaying_rect_.w = m_displaying_rect_.w * RenderingConstants::kScaleMultiplier;
    m_displaying_rect_.x = (int)(position.X() * (float)RenderingConstants::kScaleMultiplier);
    m_displaying_rect_.y = (int)(position.Y() * (float)RenderingConstants::kScaleMultiplier);

    SDL_RenderCopy(m_window_handles_->Renderer(), m_platform_texture_, nullptr, &m_displaying_rect_);
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
    free(m_platform_texture_);
}

//----------------------------------------------------------------------------------------------------
