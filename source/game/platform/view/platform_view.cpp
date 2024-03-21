#include "platform_view.h"
#include "../../rendering/rendering_constants.h"
#include "../../Shortcuts/shortcuts.h"
#include "SDL_image.h"

PlatformView::PlatformView(const WindowReferences &window_references)
    : m_window_references_(window_references)
{
    m_platform_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/platform.png");
}

void PlatformView::Display(Vector2 position) const
{
    SDL_Rect temp_rect = { };
    SDL_QueryTexture(m_platform_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);

    temp_rect.h = temp_rect.h * RenderingConstants::kScaleMultiplier;
    temp_rect.w = temp_rect.w * RenderingConstants::kScaleMultiplier;
    temp_rect.x = (int)(position.X() * (float)RenderingConstants::kScaleMultiplier);
    temp_rect.y = (int)(position.Y() * (float)RenderingConstants::kScaleMultiplier);

    SDL_RenderCopy(m_window_references_.Renderer(), m_platform_texture_, nullptr, &temp_rect);
}

PlatformView::~PlatformView()
{
    SDL_DestroyTexture(m_platform_texture_);
}
