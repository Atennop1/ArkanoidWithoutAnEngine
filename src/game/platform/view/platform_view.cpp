#include "platform_view.hpp"
#include "../../rendering/rendering_constants.hpp"
#include "../../shortcuts/shortcuts.hpp"
#include "SDL_image.h"

arkanoid::PlatformView::PlatformView(const WindowReferences &window_references) : window_references_(window_references)
{
    platform_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/platform.png");
}

void arkanoid::PlatformView::Display(arkanoid::Vector2 position) const
{
    SDL_Rect temp_rect = { };
    SDL_QueryTexture(platform_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);

    temp_rect.h = temp_rect.h * RenderingConstants::kScaleMultiplier;
    temp_rect.w = temp_rect.w * RenderingConstants::kScaleMultiplier;
    temp_rect.x = (int)(position.X() * (float)RenderingConstants::kScaleMultiplier);
    temp_rect.y = (int)(position.Y() * (float)RenderingConstants::kScaleMultiplier);

    SDL_RenderCopy(window_references_.Renderer(), platform_texture_, nullptr, &temp_rect);
}

arkanoid::PlatformView::~PlatformView()
{
    SDL_DestroyTexture(platform_texture_);
}
