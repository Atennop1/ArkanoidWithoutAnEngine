#pragma once
#include <array>
#include "Windows.h"

#include "../../DTOs/render_pack/render_pack.h"
#include "../../DTOs/vector2/int_vector2.h"

class LevelView
{
private:
    const int m_brick_width_ = 15;
    const int m_brick_height_ = 7;

    const int m_cell_width_ = m_brick_width_ + 1;
    const int m_cell_height_ = m_brick_height_ + 1;

    const int m_level_offset_x_ = 8;
    const int m_level_offset_y_ = 6;
    
    RenderPack m_violet_render_pack_;
    RenderPack m_blue_render_pack_;

    void RenderBrick(HDC hdc, IntVector2 position, RenderPack render_pack) const;
    
public:
    LevelView(RenderPack violet_render_pack, RenderPack blue_render_pack);
    void Render(HDC hdc, const std::array<std::array<char, 12>, 14> *level) const;
};

