#include "LevelRendering.h"
#include "../RenderingConsts.h"

enum BrickType
{
    BT_None = 0,
    BT_Violet = 1,
    BT_Blue = 2
};

constexpr int BRICK_WIDTH = 15;
constexpr int BRICK_HEIGHT = 7;

constexpr int CELL_WIDTH = BRICK_WIDTH + 1;
constexpr int CELL_HEIGHT = BRICK_HEIGHT + 1;

constexpr int LEVEL_OFFSET_X = 8;
constexpr int LEVEL_OFFSET_Y = 6;

extern HPEN VioletPen, BluePen;
extern HBRUSH VioletBrush, BlueBrush;

//----------------------------------------------------------------------------------------------------
void DrawBrick(HDC hdc, HPEN pen, HBRUSH brush, int x, int y)
{
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------
void RenderLevel(HDC hdc, char level[14][12])
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (level[i][j] != 1 && level[i][j] != 2)
                continue;

            const HBRUSH brush = level[i][j] == 1 ? VioletBrush : BlueBrush;
            const HPEN pen = level[i][j] == 1 ? VioletPen : BluePen;
            DrawBrick(hdc, pen, brush, LEVEL_OFFSET_X + CELL_WIDTH * j, LEVEL_OFFSET_Y + CELL_HEIGHT * i);
        }
    }
}

//----------------------------------------------------------------------------------------------------