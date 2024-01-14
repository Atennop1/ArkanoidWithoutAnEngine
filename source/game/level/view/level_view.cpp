#include "level_view.h"
#include "../../rendering/rendering_constants.h"
#include "../constants/levels.h"
#include "SDL_image.h"

LevelView::LevelView(const WindowReferences &window_references)
    : m_window_references_(window_references)
{
    m_blue_brick_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/blue_brick.png");
    m_violet_brick_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/violet_brick.png");

    SDL_Rect temp_rect { };
    SDL_QueryTexture(m_blue_brick_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);
    m_brick_height_ = temp_rect.h;
    m_brick_width_ = temp_rect.w;
}

LevelView::~LevelView()
{
    free(m_blue_brick_texture_);
    free(m_violet_brick_texture_);
}

void LevelView::Display(const std::array<std::array<char, 12>, 14> &level) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (level[i][j] == 0)
                continue;

            SDL_Texture *texture = level[i][j] == 1 ? m_violet_brick_texture_ : m_blue_brick_texture_;
            DisplayBrick(texture, IntVector2(m_level_offset_x_ + (m_brick_width_ + 1) * j, m_level_offset_y_ + (m_brick_height_ + 1) * i));
        }
    }
}

void LevelView::DisplayBrick(SDL_Texture *texture, const IntVector2 position) const
{
    SDL_Rect temp_rect { };

    temp_rect.h = m_brick_height_ * RenderingConstants::kScaleMultiplier;
    temp_rect.w = m_brick_width_ * RenderingConstants::kScaleMultiplier;
    temp_rect.x = position.X() * RenderingConstants::kScaleMultiplier;
    temp_rect.y = position.Y() * RenderingConstants::kScaleMultiplier;

    SDL_RenderCopy(m_window_references_.Renderer(), texture, nullptr, &temp_rect);
}
