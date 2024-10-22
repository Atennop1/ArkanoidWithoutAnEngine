#include "game/level/level_view.hpp"
#include "SDL_image.h"
#include "game/shortcuts/shortcuts.hpp"
#include "game/rendering/rendering_constants.hpp"

namespace arkanoid
{
LevelView::LevelView(const WindowReferences &window_references) : window_references_(window_references)
{
    blue_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/blue_brick.png");
    violet_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/violet_brick.png");
    SDL_QueryTexture(blue_brick_texture_, nullptr, nullptr, &brick_width_, &brick_height_);

    brick_width_ *= RenderingConstants::kScaleMultiplier;
    brick_height_ *= RenderingConstants::kScaleMultiplier;
}

LevelView::~LevelView()
{
    SDL_DestroyTexture(blue_brick_texture_);
    SDL_DestroyTexture(violet_brick_texture_);
}

void LevelView::Display(const LevelMap &map) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (map[i][j] == 0)
                continue;

            SDL_Texture *texture = map[i][j] == 1 ? violet_brick_texture_ : blue_brick_texture_;
            SDL_Rect rect = Shortcuts::PositionAndTextureToRect(Vector2(level_offset_x_ + (brick_width_ + 6.0f) * j, level_offset_y_ + (brick_height_ + 6.0f) * i), texture);
            SDL_RenderCopy(window_references_.Renderer(), texture, nullptr, &rect);
        }
    }
}
}
