#include "Engine.h"
#include "Rendering/Level/LevelRendering.h"
#include "Rendering/Platform/PlatformRendering.h"

extern char FirstLevel[14][12];

HPEN VioletPen, BluePen;
HBRUSH VioletBrush, BlueBrush;

//----------------------------------------------------------------------------------------------------
void CreatePenAndBrush(COLORREF color, HPEN* pen, HBRUSH* brush)
{
    *pen = CreatePen(PS_SOLID, 0, color);
    *brush = CreateSolidBrush(color);
}

//----------------------------------------------------------------------------------------------------
void Init()
{
    CreatePenAndBrush(RGB(255, 85, 255), &VioletPen, &VioletBrush);
    CreatePenAndBrush(RGB(85, 255, 255), &BluePen, &BlueBrush);
}

//----------------------------------------------------------------------------------------------------
void Update(HDC hdc)
{
    RenderLevel(hdc, FirstLevel);
    RenderPlatform(hdc, 50, 100);
}

//----------------------------------------------------------------------------------------------------
