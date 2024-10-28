#include <SDL_image.h>
#include "game/wall/wall_view.hpp"
#include "game/shortcuts/shortcuts.hpp"

namespace arkanoid
{
WallView::WallView(const WindowReferences &window_references, const char *texture_file_path) : window_references_(window_references)
{
    wall_texture_ = IMG_LoadTexture(window_references_.Renderer(), texture_file_path);
}

WallView::~WallView()
{
    SDL_DestroyTexture(wall_texture_);
}

void WallView::Display(Vector2 position) const
{
    SDL_Rect rect = Shortcuts::PositionAndTextureToRect(position, wall_texture_);
    SDL_RenderCopy(window_references_.Renderer(), wall_texture_, nullptr, &rect);
}
}
