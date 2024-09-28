#include "level_view.hpp"
#include "../../rendering/rendering_constants.hpp"
#include "SDL_image.h"

arkanoid::LevelView::LevelView(const WindowReferences &window_references) : m_window_references_(window_references)
{
    m_blue_brick_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/blue_brick.png");
    m_violet_brick_texture_ = IMG_LoadTexture(m_window_references_.Renderer(), "assets/sprites/violet_brick.png");

    SDL_Rect temp_rect { };
    SDL_QueryTexture(m_blue_brick_texture_, nullptr, nullptr, &temp_rect.w, &temp_rect.h);
    m_brick_height_ = temp_rect.h;
    m_brick_width_ = temp_rect.w;
}

arkanoid::LevelView::~LevelView()
{
    SDL_DestroyTexture(m_blue_brick_texture_);
    SDL_DestroyTexture(m_violet_brick_texture_);
}

void arkanoid::LevelView::Display(const LevelMap &map) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (map[i][j] == 0)
                continue;

            SDL_Texture *texture = map[i][j] == 1 ? m_violet_brick_texture_ : m_blue_brick_texture_;
            DisplayBrick(texture, box2d::Vector2(m_level_offset_x_ + (m_brick_width_ + 1.0f) * j, m_level_offset_y_ + (m_brick_height_ + 1.0f) * i));
        }
    }
}

void arkanoid::LevelView::DisplayBrick(SDL_Texture *texture, const box2d::Vector2 position) const
{
    SDL_Rect temp_rect { };

    temp_rect.h = m_brick_height_ * RenderingConstants::m_k_scale_multiplier_;
    temp_rect.w = m_brick_width_ * RenderingConstants::m_k_scale_multiplier_;
    temp_rect.x = position.m_x_ * RenderingConstants::m_k_scale_multiplier_;
    temp_rect.y = position.m_y_ * RenderingConstants::m_k_scale_multiplier_;

    SDL_RenderCopy(m_window_references_.Renderer(), texture, nullptr, &temp_rect);
}
