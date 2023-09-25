#include <array>
#include "LevelRenderer.h"
#include "../RenderingConsts.h"

enum BrickType
{
    BT_None = 0,
    BT_Violet = 1,
    BT_Blue = 2
};

//----------------------------------------------------------------------------------------------------
LevelRenderer::LevelRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack)
{
    m_blueRenderPack = blueRenderPack;
    m_violetRenderPack =violetRenderPack;
}

//----------------------------------------------------------------------------------------------------
void LevelRenderer::DrawBrick(HDC hdc, RenderPack renderPack, int x, int y) const
{
    SelectObject(hdc, renderPack.Pen());
    SelectObject(hdc, renderPack.Brush());
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------
void LevelRenderer::Render(HDC hdc, const array<array<char, 12>, 14> &level) const
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (level[i][j] != 1 && level[i][j] != 2)
                continue;

            const RenderPack renderPack = level[i][j] == 1 ? m_violetRenderPack : m_blueRenderPack;
            DrawBrick(hdc, renderPack, LEVEL_OFFSET_X + CELL_WIDTH * j, LEVEL_OFFSET_Y + CELL_HEIGHT * i);
        }
    }
}

//----------------------------------------------------------------------------------------------------