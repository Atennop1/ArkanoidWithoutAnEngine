#include "game/platform/platform_view.hpp"
#include "game/shortcuts/shortcuts.hpp"
#include "SDL_image.h"

namespace arkanoid
{
PlatformView::PlatformView(const WindowReferences &window_references) : window_references_(window_references)
{
    platform_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/platform.png");
}

PlatformView::~PlatformView()
{
    SDL_DestroyTexture(platform_texture_);
}

void PlatformView::Display(Vector2 position) const
{
    SDL_Rect rect = Shortcuts::PositionAndTextureToRect(position, platform_texture_);
    SDL_RenderCopy(window_references_.Renderer(), platform_texture_, nullptr, &rect);
}
}
