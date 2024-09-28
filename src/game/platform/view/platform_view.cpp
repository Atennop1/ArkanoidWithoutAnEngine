#include "platform_view.hpp"
#include "../../rendering/rendering_constants.hpp"
#include "../../shortcuts/shortcuts.hpp"
#include "SDL_image.h"

arkanoid::PlatformView::PlatformView(const WindowReferences &window_references) : m_window_references_(window_references)
{
    m_platform_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/platform.png");
}

void arkanoid::PlatformView::Display(box2d::Vector2 position) const
{
    SDL_Rect temp_rect = { };
    SDL_QueryTexture(m_platform_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);

    temp_rect.h = temp_rect.h * RenderingConstants::m_k_scale_multiplier_;
    temp_rect.w = temp_rect.w * RenderingConstants::m_k_scale_multiplier_;
    temp_rect.x = (int)(position.m_x_ * (float)RenderingConstants::m_k_scale_multiplier_);
    temp_rect.y = (int)(position.m_y_ * (float)RenderingConstants::m_k_scale_multiplier_);

    SDL_RenderCopy(m_window_references_.Renderer(), m_platform_texture_, nullptr, &temp_rect);
}

arkanoid::PlatformView::~PlatformView()
{
    SDL_DestroyTexture(m_platform_texture_);
}
