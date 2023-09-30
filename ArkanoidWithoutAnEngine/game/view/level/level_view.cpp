#include <array>
#include "level_view.h"
#include "../visualization_consts.h"
#include "../../Shortcuts/shortcuts.h"

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
            RenderBrick(hdc, Vector2(kLevelOffsetX + kCellWidth * j, kLevelOffsetY + kCellHeight * i), render_pack);
        }
    }
}

//----------------------------------------------------------------------------------------------------
void LevelView::RenderBrick(HDC hdc, Vector2 position, RenderPack render_pack) const
{
    const int x = position.X();
    const int y = position.Y();
    
    Shortcuts::SelectRenderPack(hdc, render_pack);
    RoundRect(hdc, x * kScaleMultiplier, y * kScaleMultiplier, (x + kBrickWidth) * kScaleMultiplier, (y + kBrickHeight) * kScaleMultiplier, 2 * kScaleMultiplier, 2 * kScaleMultiplier);
}

//----------------------------------------------------------------------------------------------------