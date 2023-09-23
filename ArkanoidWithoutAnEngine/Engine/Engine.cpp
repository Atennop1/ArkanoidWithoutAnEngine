#include "Engine.h"

#define BRICK_WIDTH 15
#define BRICK_HEIGHT 7

#define CELL_WIDTH (BRICK_WIDTH + 1)
#define CELL_HEIGHT (BRICK_HEIGHT + 1)

#define LEVEL_OFFSET_X 8
#define LEVEL_OFFSET_Y 6

enum BrickType
{
    BT_None,
    BT_Violet,
    BT_Blue
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
void DrawBrick(HDC hdc, COLORREF color, int x, int y)
{
    const HPEN pen = CreatePen(PS_SOLID, 0, color);
    const HBRUSH brush = CreateSolidBrush(color);

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + BRICK_WIDTH) * SCALE_MULTIPLIER, (y + BRICK_HEIGHT) * SCALE_MULTIPLIER, 10, 10);
}

//----------------------------------------------------------------------------------------------------
void DrawLevel(HDC hdc)
{
    constexpr COLORREF violet = RGB(255, 85, 255);
    constexpr COLORREF blue = RGB(85, 255, 255);
    
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            COLORREF color;
            
            switch (FirstLevel[i][j])
            {
            case 2:
                color = blue;
                break;

            case 1:
                color = violet;
                break;
                
            default:
                continue;
            }
            
            DrawBrick(hdc, color, LEVEL_OFFSET_X + CELL_WIDTH * j, LEVEL_OFFSET_Y + CELL_HEIGHT * i);
        }
    }
}

//----------------------------------------------------------------------------------------------------
void Update(HDC hdc)
{
    DrawLevel(hdc);
}

//----------------------------------------------------------------------------------------------------
