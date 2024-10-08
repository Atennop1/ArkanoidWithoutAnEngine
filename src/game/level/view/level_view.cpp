#include "level_view.hpp"
#include "../../rendering/rendering_constants.hpp"
#include "SDL_image.h"

arkanoid::LevelView::LevelView(const WindowReferences &window_references) : window_references_(window_references)
{
    blue_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/blue_brick.png");
    violet_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/violet_brick.png");

    SDL_Rect temp_rect { };
    SDL_QueryTexture(blue_brick_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);
    brick_height_ = temp_rect.h;
    brick_width_ = temp_rect.w;
}

arkanoid::LevelView::~LevelView()
{
    SDL_DestroyTexture(blue_brick_texture_);
    SDL_DestroyTexture(violet_brick_texture_);
}

void arkanoid::LevelView::Display(const LevelMap &map) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (map[i][j] == 0)
                continue;

            SDL_Texture *texture = map[i][j] == 1 ? violet_brick_texture_ : blue_brick_texture_;
            DisplayBrick(texture, arkanoid::Vector2(level_offset_x_ + (brick_width_ + 1.0f) * j, level_offset_y_ + (brick_height_ + 1.0f) * i));
        }
    }
}

void arkanoid::LevelView::DisplayBrick(SDL_Texture *texture, const arkanoid::Vector2 position) const
{
    SDL_Rect temp_rect { };

    temp_rect.h = brick_height_ * RenderingConstants::kScaleMultiplier;
    temp_rect.w = brick_width_ * RenderingConstants::kScaleMultiplier;
    temp_rect.x = position.X() * RenderingConstants::kScaleMultiplier;
    temp_rect.y = position.Y() * RenderingConstants::kScaleMultiplier;

    SDL_RenderCopy(window_references_.Renderer(), texture, nullptr, &temp_rect);
}
