#include "PlatformRendering.h"
#include "../RenderingConsts.h"

constexpr int PLATFORM_CIRCLE_SIZE = 7;
constexpr int PLATFORM_WIDTH = 21;

extern HPEN VioletPen, BluePen;
extern HBRUSH VioletBrush, BlueBrush;

//----------------------------------------------------------------------------------------------------
void RenderPlatform(HDC hdc, int x, int y)
{
    SelectObject(hdc, VioletPen);
    SelectObject(hdc, VioletBrush);
    
    Ellipse(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);
    Ellipse(hdc, (x + PLATFORM_WIDTH) * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE + PLATFORM_WIDTH) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);

    SelectObject(hdc, BluePen);
    SelectObject(hdc, BlueBrush);
    RoundRect(hdc, (x + 3) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + 5 + PLATFORM_WIDTH - 1) * SCALE_MULTIPLIER, (y + 1 + 5) * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------