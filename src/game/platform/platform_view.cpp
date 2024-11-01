#include <genesis/shortcuts/shortcuts.hpp>
#include "game/platform/platform_view.hpp"
#include "SDL2/SDL_image.h"

namespace arkanoid
{
PlatformView::PlatformView(genesis::WindowReferences window_references) : window_references_(window_references)
{
    platform_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/platform.png");
}

PlatformView::~PlatformView()
{
    SDL_DestroyTexture(platform_texture_);
}

void PlatformView::Display(genesis::Vector2 position) const
{
    SDL_FRect rect = genesis::Shortcuts::PositionAndTextureToRect(position, platform_texture_, 6, 6);
    SDL_RenderCopyF(window_references_.Renderer(), platform_texture_, nullptr, &rect);
}
}
