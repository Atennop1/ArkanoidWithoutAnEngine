#pragma once

#include "Windows.h"
#include "../RenderPack/RenderPack.h"
using namespace std;

class LevelRenderer
{
private:
    const int BRICK_WIDTH = 15;
    const int BRICK_HEIGHT = 7;

    const int CELL_WIDTH = BRICK_WIDTH + 1;
    const int CELL_HEIGHT = BRICK_HEIGHT + 1;

    const int LEVEL_OFFSET_X = 8;
    const int LEVEL_OFFSET_Y = 6;
    
    RenderPack m_violetRenderPack;
    RenderPack m_blueRenderPack;

    void DrawBrick(HDC hdc, RenderPack renderPack, int x, int y) const;
    
public:
    LevelRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack);
    void Render(HDC hdc, const array<array<char, 12>, 14>&) const;
};

