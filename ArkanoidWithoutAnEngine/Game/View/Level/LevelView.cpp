#include <array>
#include "LevelView.h"
#include "..\VisualizationConsts.h"
#include "../../Shortcuts/Shortcuts.h"

//----------------------------------------------------------------------------------------------------
LevelView::LevelView(RenderPack violetRenderPack, RenderPack blueRenderPack)
{
    m_blueRenderPack = blueRenderPack;
    m_violetRenderPack = violetRenderPack;
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

            const RenderPack renderPack = (*level)[i][j] == 1 ? m_violetRenderPack : m_blueRenderPack;
            RenderBrick(hdc, Vector2(LEVEL_OFFSET_X + CELL_WIDTH * j, LEVEL_OFFSET_Y + CELL_HEIGHT * i), renderPack);
        }
    }
}

//----------------------------------------------------------------------------------------------------
void LevelView::RenderBrick(HDC hdc, Vector2 position, RenderPack renderPack) const
{
    const int x = position.X();
    const int y = position.Y();
    
    Shortcuts::SelectRenderPack(hdc, renderPack);
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------