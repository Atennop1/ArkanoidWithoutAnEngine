#include <SDL2/SDL_image.h>
#include "game/wall/wall_view.hpp"
#include "genesis/shortcuts/shortcuts.hpp"

namespace arkanoid
{
WallView::WallView(genesis::WindowReferences window_references, const char *texture_file_path) : window_references_(window_references)
{
    wall_texture_ = IMG_LoadTexture(window_references_.Renderer(), texture_file_path);
}

WallView::~WallView()
{
    SDL_DestroyTexture(wall_texture_);
}

void WallView::Display(genesis::Vector2 position) const
{
    SDL_FRect rect = genesis::Shortcuts::PositionAndTextureToRect(position, wall_texture_, 6, 6);
    SDL_RenderCopyF(window_references_.Renderer(), wall_texture_, nullptr, &rect);
}
}
