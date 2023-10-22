#include <array>
#include "level_view.h"
#include "../Shortcuts/shortcuts.h"
#include "../rendering/rendering_consts.h"

//----------------------------------------------------------------------------------------------------
LevelView::LevelView(RenderPack violet_render_pack, RenderPack blue_render_pack)
{
    m_blue_render_pack_ = blue_render_pack;
    m_violet_render_pack_ = violet_render_pack;
}

//----------------------------------------------------------------------------------------------------
void LevelView::Render(HDC hdc, const std::array<std::array<char, 12>, 14> *level) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if ((*level)[i][j] != 1 && (*level)[i][j] != 2)
                continue;

            const RenderPack render_pack = (*level)[i][j] == 1 ? m_violet_render_pack_ : m_blue_render_pack_;
            RenderBrick(hdc, IntVector2(m_level_offset_x_ + m_cell_width_ * j, m_level_offset_y_ + m_cell_height_ * i), render_pack);
        }
    }
}

//----------------------------------------------------------------------------------------------------
void LevelView::RenderBrick(HDC hdc, IntVector2 position, RenderPack render_pack) const
{
    Shortcuts::SelectRenderPack(hdc, render_pack);
    RoundRect(hdc, position.X() * kScaleMultiplier, position.Y() * kScaleMultiplier, (position.X() + m_brick_width_) * kScaleMultiplier, (position.Y() + m_brick_height_) * kScaleMultiplier, 2 * kScaleMultiplier, 2 * kScaleMultiplier);
}

//----------------------------------------------------------------------------------------------------