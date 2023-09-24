#include "Engine.h"
#include <C:\Users\User\source\repos\ArkanoidWithoutAnEngine\ArkanoidWithoutAnEngine\Engine\RenderingConsts.h>

constexpr int BRICK_WIDTH = 15;

constexpr int BRICK_HEIGHT = 7;

constexpr int CELL_WIDTH = BRICK_WIDTH + 1;
constexpr int CELL_HEIGHT = BRICK_HEIGHT + 1;

constexpr int LEVEL_OFFSET_X = 8;
constexpr int LEVEL_OFFSET_Y = 6;

constexpr int PLATFORM_CIRCLE_SIZE = 7;
constexpr int PLATFORM_WIDTH = 21;

HPEN violetPen;
HPEN bluePen;

HBRUSH violetBrush;
HBRUSH blueBrush;

enum BrickType
{
    BT_None = 0,
    BT_Violet = 1,
    BT_Blue = 2
};

int FirstLevel[14][12]
{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

//----------------------------------------------------------------------------------------------------
void CreatePenAndBrush(COLORREF color, HPEN* pen, HBRUSH* brush)
{
    *pen = CreatePen(PS_SOLID, 0, color);
    *brush = CreateSolidBrush(color);
}

//----------------------------------------------------------------------------------------------------
void Init()
{
    CreatePenAndBrush(RGB(255, 85, 255), &violetPen, &violetBrush);
    CreatePenAndBrush(RGB(85, 255, 255), &bluePen, &blueBrush);
}

//----------------------------------------------------------------------------------------------------
void DrawBrick(HDC hdc, HPEN pen, HBRUSH brush, int x, int y)
{
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER, 2 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------
void DrawLevel(HDC hdc)
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (FirstLevel[i][j] != 1 && FirstLevel[i][j] != 2)
                continue;

            const HBRUSH brush = FirstLevel[i][j] == 1 ? violetBrush : blueBrush;
            const HPEN pen = FirstLevel[i][j] == 1 ? violetPen : bluePen;
            DrawBrick(hdc, pen, brush, LEVEL_OFFSET_X + CELL_WIDTH * j, LEVEL_OFFSET_Y + CELL_HEIGHT * i);
        }
    }
}

//----------------------------------------------------------------------------------------------------
void DrawPlatform(HDC hdc, int x, int y)
{
    SelectObject(hdc, violetPen);
    SelectObject(hdc, violetBrush);
    
    Ellipse(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);
    Ellipse(hdc, (x + PLATFORM_WIDTH) * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE + PLATFORM_WIDTH) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);

    SelectObject(hdc, bluePen);
    SelectObject(hdc, blueBrush);
    RoundRect(hdc, (x + 3) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + 5 + PLATFORM_WIDTH - 1) * SCALE_MULTIPLIER, (y + 1 + 5) * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------
void Update(HDC hdc)
{
    DrawLevel(hdc);
    DrawPlatform(hdc, 50, 100);
}

//----------------------------------------------------------------------------------------------------
