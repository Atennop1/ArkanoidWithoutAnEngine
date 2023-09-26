#include <array>
#include "LevelRenderer.h"
#include "../RenderingConsts.h"
#include "../../Shortcuts/Shortcuts.h"

//----------------------------------------------------------------------------------------------------
LevelRenderer::LevelRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack)
{
    m_blueRenderPack = blueRenderPack;
    m_violetRenderPack = violetRenderPack;
}

//----------------------------------------------------------------------------------------------------
void LevelRenderer::Render(HDC hdc, const std::array<std::array<char, 12>, 14> *level) const
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
void LevelRenderer::RenderBrick(HDC hdc, Vector2 position, RenderPack renderPack) const
{
    Shortcuts::SelectRenderPack(hdc, renderPack);
    RoundRect(hdc, position.X * SCALE_MULTIPLIER, position.Y * SCALE_MULTIPLIER, (position.X + BRICK_WIDTH) * SCALE_MULTIPLIER, (position.Y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------